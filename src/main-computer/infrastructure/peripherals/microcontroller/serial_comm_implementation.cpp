#include "serial_comm.h"

#include "CommDataError.h"
#include "CommInitError.h"
#include "CommTimeoutError.h"
using infrastructure::microcontroller::CommDataError;
using infrastructure::microcontroller::CommInitError;
using infrastructure::microcontroller::CommTimeoutError;

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <arpa/inet.h>
#include <cmath>
using std::fabs;

static constexpr const char* TTY_PATH = "/dev/ttyACM0";
static constexpr int TIMEOUT_WINDOW = 20; // Tenths of a second

static int tty;

void serial_comm_send(const uint16_t msg) {
    uint16_t network_msg = htons(msg);
    bool successful = false;
    unsigned bytes, new_bytes;
    uint8_t checksum, response;

	for(unsigned i = 0; i < ATTEMPTS_BEFORE_ABORT; i++)
	{
		bytes = 0;
	    while (bytes < sizeof(network_msg))
	    {
	    	bytes += write(tty, (uint8_t*)&network_msg + bytes, sizeof(network_msg) - bytes);
	    }

	    checksum = (network_msg & 0x00ff) + (network_msg >> 8 & 0x00ff);
	    write(tty, &checksum, sizeof(checksum));

	    new_bytes = read(tty, &response, sizeof(response));

    	if (new_bytes == 0)
    	{
    		throw CommTimeoutError();
    	}

	    if (fabs((int)response - ACKNOWLEDGE) < fabs((int)response - NEGATIVE_ACKNOWLEDGE))
	    {
	        successful = true;

	        break;
	    }
	}

	if (!successful)
	{
		throw CommDataError();
	}
}

uint16_t serial_comm_receive() {
    uint16_t network_msg;
    bool successful = false;
    unsigned bytes, new_bytes;
    uint8_t checksum;

    for(unsigned i = 0; i < ATTEMPTS_BEFORE_ABORT; i++)
    {
        bytes = 0;
        while (bytes < sizeof(network_msg))
        {
            new_bytes = read(tty, (uint8_t*)&network_msg + bytes, sizeof(network_msg) - bytes);

            if (new_bytes == 0)
            {
                throw CommTimeoutError();
            }

            bytes += new_bytes;
        }

        new_bytes = read(tty, &checksum, sizeof(checksum));

        if (new_bytes == 0)
        {
            throw CommTimeoutError();
        }

        if ((uint8_t)((network_msg & 0x00ff) + (network_msg >> 8 & 0x00ff)) == checksum)
        {
            write(tty, &ACKNOWLEDGE, sizeof(ACKNOWLEDGE));

            successful = true;

            break;
        }
        else
        {
            write(tty, &NEGATIVE_ACKNOWLEDGE, sizeof(NEGATIVE_ACKNOWLEDGE));
        }
    }

    if (!successful)
    {
        throw CommDataError();
    }

    return ntohs(network_msg);
}

int baud2constant(const int baud)
{
    switch (baud)
    {
        case 4800: return B4800;
        case 9600: return B9600;
        case 19200: return B19200;
        case 38400: return B38400;
        case 57600: return B57600;
    }
    return -1;
}

struct Init {
    Init();
    ~Init();
} init;

Init::Init() {
    tty = open(TTY_PATH, O_RDWR | O_NOCTTY);
    if (tty == -1)
    {
        throw CommInitError();
    }
    else
    {
        fcntl(tty, F_SETFL, 0);
    }

    struct termios options;
    tcgetattr(tty, &options);

    // Set baud rate
    cfsetispeed(&options, baud2constant(BAUD_RATE));
    cfsetospeed(&options, baud2constant(BAUD_RATE));

    // Necessary flags
    options.c_cflag |= (CLOCAL | CREAD);

    // Set character size and disable parity
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // Enable the following line if parity is turned on
    // options.c_iflag |= (INPCK | ISTRIP); //Enable parity check and strip

    // Disable hardware and software flow control respectively
    options.c_cflag &= ~CRTSCTS;
    options.c_iflag &= ~(IXON | IXOFF | IXANY);

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Enable raw input

    options.c_oflag &= ~OPOST; // Enable raw output

    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = TIMEOUT_WINDOW;

    tcsetattr(tty, TCSANOW, &options);
}

Init::~Init() {
    close(tty);
}

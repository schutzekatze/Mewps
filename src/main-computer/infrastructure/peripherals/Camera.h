/*
 * Camera.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_CAMERA_H_
#define INFRASTRUCTURE_PERIPHERALS_CAMERA_H_

namespace infrastructure
{

class Camera
{

public:

    // Multiple readers/writers problem
    static const unsigned char* get_frame();

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_CAMERA_H_ */

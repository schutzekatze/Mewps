/*
 * Compass.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_COMPASS_H
#define INFRASTRUCTURE_PERIPHERALS_COMPASS_H

namespace infrastructure {

// Threadsafe
class Compass {

public:

    static float get_orientation();

private:

    static constexpr float CONVERSION_FACTOR = 0.1;

    Compass() = delete;

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_COMPASS_H */

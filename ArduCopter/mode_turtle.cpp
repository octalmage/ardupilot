#include "Copter.h"
#include "mode.h"

#if MODE_TURTLE_ENABLED == ENABLED

/*
 * Init and run calls for turtle flight mode
 */


// turtle_init - initialise turtle controller
bool ModeTurtle::init(bool ignore_checks)
{   

    #if FRAME_CONFIG == HELI_FRAME
        // do not allow helis to use turtle mode
        return false;
    #endif

    // we don't want the motors enabled while upside down.
    copter.air_mode = AirMode::AIRMODE_DISABLED;


    // set target to current position
    // TODO: Run dshot command to reverse motors? 

    // DSHOT command 20 will set the motor direction to normal, and 21 will reverse.
    return true;
}

// turtle_run - runs the turtle controller
void ModeTurtle::run()
{
   // TODO: Check stick position and move the corresponding motor.
}

void ModeTurtle::exit()
{
    // TODO: Set airmode to it's previous state.
    //  if (g2.acro_options.get() & uint8_t(AcroOptions::AIR_MODE)) {
    //     copter.air_mode = AirMode::AIRMODE_ENABLED;
    // }

    // TODO: Use DSHOT commant to set motor direction to normal.
}

#endif

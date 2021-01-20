#include "Copter.h"

#if MODE_TURTLE_ENABLED == ENABLED

/*
 * Init and run calls for turtle flight mode
 */

// turtle_init - initialise turtle controller
bool ModeTurtle::init(bool ignore_checks)
{
    // set target to current position
    // TODO: Run initialization like reversing motors? 

    // DSHOT command 20 will set the motor direction to normal, and 21 will reverse.
    return true;
}

// turtle_run - runs the turtle controller
void ModeTurtle::run()
{
   // TODO: Check stick position and move the corresponding motor.
}

#endif

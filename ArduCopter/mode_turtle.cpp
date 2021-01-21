#include "Copter.h"
#include "mode.h"

#if MODE_TURTLE_ENABLED == ENABLED

/*
 * Init and run calls for turtle flight mode
 */


// turtle_init - initialise turtle controller
bool ModeTurtle::init(bool ignore_checks)
{   
    // do not enter the mode when already armed or when flying
    if (motors->armed()) {
         gcs().send_text(MAV_SEVERITY_INFO, "Turtle Mode Change Fail: Turtles cannot fly!!!");
        return false;
    }

     // Check that interlock is disengaged
    if (motors->get_interlock()) {
        gcs().send_text(MAV_SEVERITY_INFO, "Turtle Mode Change Fail: Interlock Engaged");
        return false;
    }

    #if FRAME_CONFIG == HELI_FRAME
        // do not allow helis to use turtle mode
        return false;
    #endif

    // we don't want the motors enabled while upside down.
    copter.air_mode = AirMode::AIRMODE_DISABLED;

    //Check to see if we are using DHOT 
    if (motors->get_pwm_type() != AP_Motors::PWM_TYPE_DSHOT150 &&
        motors->get_pwm_type() != AP_Motors::PWM_TYPE_DSHOT300 &&
        motors->get_pwm_type() != AP_Motors::PWM_TYPE_DSHOT600 &&
        motors->get_pwm_type() != AP_Motors::PWM_TYPE_DSHOT1200 ) {
        gcs().send_text(MAV_SEVERITY_INFO, "Turtle Mode Change Fail: Not using DSHOT");
        return false;
    }

    int repeat_counter;

    for (repeat_counter = 1; repeat_counter <= 10; repeat_counter++) {
        motors->output_test_seq(1, 21);
    }

    // Save request.
    motors->output_test_seq(1, 12);


    // DSHOT command 20 will set the motor direction to normal, and 21 will reverse.
    return true;
}

// turtle_run - runs the turtle controller
void ModeTurtle::run()
{
   // TODO: Check stick position and move the corresponding motor.

    if (!motors->armed()) {
        // Motors should be Stopped
        motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::SHUT_DOWN);
    } 

    switch (motors->get_spool_state()) {

    case AP_Motors::SpoolState::SHUT_DOWN:

        // TODO: Check stick position to determine throttle amount. 
        motors->output_test_seq(1, motors->output_to_pwm(get_pilot_desired_throttle()));
        break;

    case AP_Motors::SpoolState::THROTTLE_UNLIMITED:
    case AP_Motors::SpoolState::SPOOLING_UP:
    case AP_Motors::SpoolState::SPOOLING_DOWN:
    case AP_Motors::SpoolState::GROUND_IDLE:
        break;
    }

    
}

void ModeTurtle::exit()
{
    // Set airmode to it's previous state.
    if (g2.acro_options.get() & uint8_t(ModeAcro::AcroOptions::AIR_MODE)) {
        copter.air_mode = AirMode::AIRMODE_ENABLED;
    }

    int repeat_counter;
    for (repeat_counter = 1; repeat_counter <= 10; repeat_counter++) {
        motors->output_test_seq(1, 20);
    }

    // Save request.
    motors->output_test_seq(1, 12);
}

#endif

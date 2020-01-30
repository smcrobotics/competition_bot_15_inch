//
// Created by ariel on 11/15/19.
//
#ifndef ROBOT_CODE_CONSTANTS_H
#define ROBOT_CODE_CONSTANTS_H

#include "main.h"
#include "okapi/api.hpp"

using namespace okapi;
namespace robot {
    /* Begin drive motor block */
    const int FRONT_LEFT_DRIVE_MOTOR_PORT = 0;
    const int FRONT_RIGHT_DRIVE_MOTOR_PORT = 0;
    const int BACK_LEFT_DRIVE_MOTOR_PORT = 13;
    const int BACK_RIGHT_DRIVE_MOTOR_PORT = 2;
    /* End drive motor block */


    /* Begin lift block */
    const int LIFT_MOTOR_PORT_LEFT = -11; // TODO: Placeholder value
    const int LIFT_MOTOR_PORT_RIGHT = 1; // TODO: Placeholder value
    
    const char LIFT_POS_LIMIT_SWITCH_UP = 'A'; // TODO: Placeholder value
    const char LIFT_POS_LIMIT_SWITCH_DOWN = 'A'; //TODO: Placeholder value

    const float LIFT_DOWN_POS = 0;
    const float LIFT_UP_POS_LEFT = 910.0;
    const float LIFT_UP_POS_RIGHT = 910.0;
    /* End lift block */


    /* Begin claw block */
    const int CLAW_MOTOR_PORT = 15;
    const int CLAW_MOTOR_POS_OPEN = 140; // TODO: Placeholder value
    const int CLAW_MOTOR_POS_CLOSED = 0;
    /* End claw block */


    /* Begin random global pointer block */
    extern std::shared_ptr<okapi::ChassisController> chassis;
    extern std::shared_ptr<okapi::AsyncMotionProfileController> profile_controller;
    /* End random global pointer block */
}

namespace bindings {
    const auto LIFT_BUTTON  = okapi::ControllerDigital::R1; // TODO: Placeholder value
    const auto OUTTAKE_BUTTON = okapi::ControllerDigital::L1;

    const auto TOGGLE_LIFT_POS = okapi::ControllerDigital::B;
    const auto LIFT_POS_UP = okapi::ControllerDigital::up;
    const auto LIFT_POS_DOWN = okapi::ControllerDigital::left;

    const auto TOGGLE_CLAW = okapi::ControllerDigital::A;

    const auto DRIVE_BRAKE_TOGGLE = okapi::ControllerDigital::X;
}

namespace constants {
    const int MOTOR_MOVE_MAX = 127;

    const auto OKAPI_BRAKE = okapi::AbstractMotor::brakeMode::brake;
    const auto OKAPI_COAST = okapi::AbstractMotor::brakeMode::coast;
}

#endif //ROBOT_CODE_CONSTANTS_H
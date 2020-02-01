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
    const int FRONT_LEFT_DRIVE_MOTOR_PORT = 5;
    const int FRONT_RIGHT_DRIVE_MOTOR_PORT = -6;
    const int BACK_LEFT_DRIVE_MOTOR_PORT = 19;
    const int BACK_RIGHT_DRIVE_MOTOR_PORT = -20;
    /* End drive motor block */


    /* Begin lift block */
    const int LIFT_MOTOR_PORT_LEFT = -11; // TODO: Placeholder value
    const int LIFT_MOTOR_PORT_RIGHT = 10; // TODO: Placeholder value
    
    const char LIFT_POS_LIMIT_SWITCH_UP = 'A'; // TODO: Placeholder value
    const char LIFT_POS_LIMIT_SWITCH_DOWN = 'A'; //TODO: Placeholder value

    const float LIFT_DOWN_POS = 0;
    const float LIFT_UP_POS_LEFT = 1360.0;
    const float LIFT_UP_POS_RIGHT = 1360.0;
    const float LIFT_TOWER_LOW_POS_RIGHT = 100; //TODO: Placeholder value
    const float LIFT_TOWER_LOW_POS_LEFT = 100; //TODO: Placeholder value
    const float LIFT_TOWER_MID_POS_RIGHT = 500; //TODO: Placeholder value
    const float LIFT_TOWER_MID_POS_LEFT = 500; //TODO: Placeholder value
    const float LIFT_TOWER_HIGH_POS_RIGHT = 1360; //TODO: Placeholder value
    const float LIFT_TOWER_HIGH_POS_LEFT = 1360; //TODO: Placeholder value
    /* End lift block */


    /* Begin claw block */
    const int CLAW_MOTOR_PORT = 15;
    const int CLAW_MOTOR_POS_OPEN = 200; // TODO: Placeholder value
    const int CLAW_MOTOR_POS_CLOSED = 0;
    /* End claw block */


    /* Begin random global pointer block */
    extern std::shared_ptr<okapi::ChassisController> chassis;
    extern std::shared_ptr<okapi::AsyncMotionProfileController> profile_controller;
    /* End random global pointer block */
}

namespace bindings {
    const auto LIFT_POS_UP = okapi::ControllerDigital::up;
    const auto LIFT_POS_DOWN = okapi::ControllerDigital::down;
    const auto LIFT_POS_TOWER_LOW = okapi::ControllerDigital::Y; // TODO: Placeholder value
    const auto LIFT_POS_TOWER_MID = okapi::ControllerDigital::B; // TODO: Placeholder value
    const auto LIFT_POS_TOWER_HIGH = okapi::ControllerDigital::A; // TODO: Placeholder value
    const auto LIFT_MOVE_UP = okapi::ControllerDigital::R1; // TODO: Placeholder value
    const auto LIFT_MOVE_DOWN = okapi::ControllerDigital::R2; // TODO: Placeholder value

    const auto TOGGLE_CLAW = okapi::ControllerDigital::right;

    const auto DRIVE_BRAKE_TOGGLE = okapi::ControllerDigital::left;
}

namespace constants {
    const int MOTOR_MOVE_MAX = 127;

    const auto OKAPI_BRAKE = okapi::AbstractMotor::brakeMode::brake;
    const auto OKAPI_COAST = okapi::AbstractMotor::brakeMode::coast;
}

#endif //ROBOT_CODE_CONSTANTS_H
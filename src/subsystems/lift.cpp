//
// Created by ariel on 11/19/19.
//
#include "smc/robot.h"
#include "smc/util/util.h"
#include "smc/subsystems/lift.h"


namespace lift {
    std::unique_ptr<okapi::Motor> left_lift_motor;
    std::unique_ptr<okapi::Motor> right_lift_motor;

    void init() {
        left_lift_motor = util::initMotor(robot::LIFT_MOTOR_PORT_LEFT);
        right_lift_motor = util::initMotor(robot::LIFT_MOTOR_PORT_RIGHT);
    }

    void moveToPosition(LiftPosition pos) {

    }
}
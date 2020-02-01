//
// Created by ariel on 11/19/19.
// ariel is very cool
//
#include "smc/robot.h"
#include "smc/util/util.h"
#include "smc/subsystems/lift.h"

using std::cout;
using std::endl;

namespace lift {
    std::unique_ptr<okapi::Motor> left_lift_motor;
    std::unique_ptr<okapi::Motor> right_lift_motor;
    std::unique_ptr<okapi::ADIButton> top_lift_limit_switch;
    std::unique_ptr<okapi::ADIButton> bottom_lift_limit_switch;

    void init() {
        left_lift_motor = util::initMotor(robot::LIFT_MOTOR_PORT_LEFT);
        right_lift_motor = util::initMotor(robot::LIFT_MOTOR_PORT_RIGHT);
        top_lift_limit_switch = util::initLimitSwitch(robot::LIFT_POS_LIMIT_SWITCH_UP);
        bottom_lift_limit_switch = util::initLimitSwitch(robot::LIFT_POS_LIMIT_SWITCH_UP);

        left_lift_motor->tarePosition();
        right_lift_motor->tarePosition();
    }

    void update() {
        if (top_lift_limit_switch->isPressed()) {
            move(0);
        } else if (bottom_lift_limit_switch->isPressed()) {
            move(0);
            left_lift_motor->tarePosition();
            right_lift_motor->tarePosition();
        }
    }

    void moveToPosition(LiftPosition pos) {
        std::int32_t velocity = 0;

        switch (pos) {
            case UP:
                left_lift_motor->moveAbsolute(robot::LIFT_UP_POS_LEFT, UP_VELOCITY);
                right_lift_motor->moveAbsolute(robot::LIFT_UP_POS_RIGHT, UP_VELOCITY);
                break;
            case DOWN:
                left_lift_motor->moveAbsolute(robot::LIFT_DOWN_POS, DOWN_VELOCITY);
                right_lift_motor->moveAbsolute(robot::LIFT_DOWN_POS, DOWN_VELOCITY);
                break;
            case TOWER_LOW:
                velocity = (robot::LIFT_TOWER_LOW_POS_LEFT - left_lift_motor->getPosition() > 0 ? UP_VELOCITY : DOWN_VELOCITY);
                left_lift_motor->moveAbsolute(robot::LIFT_TOWER_LOW_POS_LEFT, velocity);
                right_lift_motor->moveAbsolute(robot::LIFT_TOWER_LOW_POS_RIGHT, velocity);
                break;
            case TOWER_MID:
                velocity = (robot::LIFT_TOWER_MID_POS_LEFT - left_lift_motor->getPosition() > 0 ? UP_VELOCITY : DOWN_VELOCITY);
                left_lift_motor->moveAbsolute(robot::LIFT_TOWER_MID_POS_LEFT, velocity);
                right_lift_motor->moveAbsolute(robot::LIFT_TOWER_MID_POS_RIGHT, velocity);
                break;
            case TOWER_HIGH:
                velocity = (robot::LIFT_TOWER_HIGH_POS_LEFT - left_lift_motor->getPosition() > 0 ? UP_VELOCITY : DOWN_VELOCITY);
                left_lift_motor->moveAbsolute(robot::LIFT_TOWER_HIGH_POS_LEFT, velocity);
                right_lift_motor->moveAbsolute(robot::LIFT_TOWER_HIGH_POS_RIGHT, velocity);
                break;
        }
    }

    void printPos() {
        cout << "Left: " << left_lift_motor->getPosition() << endl;
        cout << "Right: " << right_lift_motor->getPosition() << endl;
    }

    void move(std::int32_t velocity) {
        left_lift_motor->moveVelocity(velocity);
        right_lift_motor->moveVelocity(velocity);
    }
}
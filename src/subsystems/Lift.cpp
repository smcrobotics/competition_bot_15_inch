//
// Created by ariel on 11/19/19.
// ariel is very cool
//
#include "smc/robot.h"
#include "smc/util/util.h"
#include "smc/subsystems/Lift.h"

using std::cout;
using std::endl;

namespace subsystems {
    Lift::Lift() : limit_timeout_bottom(0), limit_timeout_top(0), current_pos(DOWN) {
        left_motor = util::initMotor(robot::LIFT_MOTOR_PORT_LEFT);
        right_motor = util::initMotor(robot::LIFT_MOTOR_PORT_RIGHT);
        Lift::top_limit_switch = util::initLimitSwitch(robot::LIFT_POS_LIMIT_SWITCH_UP);
        Lift::bottom_limit_switch = util::initLimitSwitch(robot::LIFT_POS_LIMIT_SWITCH_DOWN);

        left_motor->tarePosition();
        right_motor->tarePosition();
    }

    Lift * Lift::getInstance() {
        static Lift lift;
        return &lift;
    }

    void Lift::update() {
        if (Lift::top_limit_switch->isPressed() && Lift::limit_timeout_top == 0) {
            std::cout << "top limit switch pressed" << std::endl;
            if (left_motor->getActualVelocity() > 0 && right_motor->getActualVelocity() > 0) {
                left_motor->moveAbsolute(0, 1);
                right_motor->moveAbsolute(0, 1);
            }
        } else if (Lift::limit_timeout_top > 0) {
            Lift::limit_timeout_top--;
        }
        
        if (Lift::bottom_limit_switch->isPressed() && Lift::limit_timeout_bottom == 0) {
            std::cout << "bottom limit switch pressed" << std::endl;
            if (left_motor->getActualVelocity() < 0 && right_motor->getActualVelocity() < 0) {
                left_motor->moveAbsolute(0, 1);
                right_motor->moveAbsolute(0, 1);
                left_motor->tarePosition();
                right_motor->tarePosition();
            }
        } else if (Lift::limit_timeout_bottom > 0) {
            Lift::limit_timeout_bottom--;
        }
    }

    void Lift::moveToPosition(Lift::LiftPosition pos) {
        std::int32_t velocity = 0;

        switch (pos) {
            case Lift::UP:
                left_motor->moveAbsolute(robot::LIFT_UP_POS_LEFT, constants::LIFT_UP_VELOCITY);
                right_motor->moveAbsolute(robot::LIFT_UP_POS_RIGHT, constants::LIFT_UP_VELOCITY);
                break;
            case DOWN:
                left_motor->moveAbsolute(robot::LIFT_DOWN_POS, constants::LIFT_DOWN_VELOCITY);
                right_motor->moveAbsolute(robot::LIFT_DOWN_POS, constants::LIFT_DOWN_VELOCITY);
                break;
            case TOWER_LOW:
                velocity = (robot::LIFT_TOWER_LOW_POS_LEFT - left_motor->getPosition() > 0 ? constants::LIFT_UP_VELOCITY : constants::LIFT_DOWN_VELOCITY);
                left_motor->moveAbsolute(robot::LIFT_TOWER_LOW_POS_LEFT, velocity);
                right_motor->moveAbsolute(robot::LIFT_TOWER_LOW_POS_RIGHT, velocity);
                break;
            case TOWER_MID:
                velocity = (robot::LIFT_TOWER_MID_POS_LEFT - left_motor->getPosition() > 0 ? constants::LIFT_UP_VELOCITY : constants::LIFT_DOWN_VELOCITY);
                left_motor->moveAbsolute(robot::LIFT_TOWER_MID_POS_LEFT, velocity);
                right_motor->moveAbsolute(robot::LIFT_TOWER_MID_POS_RIGHT, velocity);
                break;
        }
    }

    void Lift::printDebug() {
        cout << "[DEBUG][Lift] Left target: " << left_motor->getTargetPosition() << endl;
        cout << "[DEBUG][Lift] Right target: " << right_motor->getTargetPosition() << endl;
        cout << "[DEBUG][Lift] Left actual: " << left_motor->getPosition() << endl;
        cout << "[DEBUG][Lift] Right actual: " << right_motor->getPosition() << endl;
    }

    void Lift::printLCD(int line) {
        std::ostringstream out;

        out << "[L] lpos: " << left_motor->getPosition();
        out << ", rpos: " << left_motor->getPosition();
        out << ", tt: " << Lift::limit_timeout_top;
        out << ", bt: " << Lift::limit_timeout_bottom;

        pros::lcd::clear_line(line);
        pros::lcd::set_text(line, out.str());
    }

    void Lift::waitUntilSettled() {
        while (!(left_motor->isStopped() && right_motor->isStopped()))
            pros::delay(10);
    }

    void Lift::move(std::int32_t velocity) {
        // (moving up while top limit switch is pressed) or (moving down while bottom limit switch is pressed)
        if ((velocity > 0 && Lift::top_limit_switch->isPressed()) || (velocity < 0 && Lift::bottom_limit_switch->isPressed())) {
            return;
        }

        left_motor->moveVelocity(velocity);
        right_motor->moveVelocity(velocity);
    }
}

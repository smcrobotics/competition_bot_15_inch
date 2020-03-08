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
        left_motor = util::initMotor(robot::LIFT_MOTOR_PORT_LEFT, okapi::AbstractMotor::gearset::red);
        right_motor = util::initMotor(robot::LIFT_MOTOR_PORT_RIGHT, okapi::AbstractMotor::gearset::red);
        top_limit_switch = util::initLimitSwitch(robot::LIFT_POS_LIMIT_SWITCH_UP);
        bottom_limit_switch = util::initLimitSwitch(robot::LIFT_POS_LIMIT_SWITCH_DOWN);

        left_motor->tarePosition();
        right_motor->tarePosition();
    }

    Lift * Lift::getInstance() {
        static Lift lift;
        return &lift;
    }

    void Lift::update() {
<<<<<<< HEAD
//        if (top_limit_switch->isPressed() && limit_timeout_top == 0) {
//            if (left_motor->getActualVelocity() > 0 && right_motor->getActualVelocity() > 0) {
//                left_motor->moveAbsolute(left_motor->getPosition(), 1);
//                right_motor->moveAbsolute(right_motor->getPosition(), 1);
//            }
//        } else if (limit_timeout_top > 0) {
//            limit_timeout_top--;
//        }
//
//        if (bottom_limit_switch->isPressed() && limit_timeout_bottom == 0) {
//            if (left_motor->getActualVelocity() < 0 && right_motor->getActualVelocity() < 0) {
//                left_motor->tarePosition();
//                right_motor->tarePosition();
//                left_motor->moveAbsolute(0, 1);
//                right_motor->moveAbsolute(0, 1);
//            }
//        } else if (limit_timeout_bottom > 0) {
//            limit_timeout_bottom--;
//        }
=======
        if (top_limit_switch->isPressed() && limit_timeout_top == 0) {
            if (left_motor->getActualVelocity() > 0 && right_motor->getActualVelocity() > 0) {
                left_motor->moveAbsolute(left_motor->getPosition(), 1);
                right_motor->moveAbsolute(right_motor->getPosition(), 1);
                // limit_timeout_top = 1000;
            }
        } else if (limit_timeout_top > 0) {
            limit_timeout_top--;
        }
        
        if (bottom_limit_switch->isPressed() && limit_timeout_bottom == 0) {
            left_motor->tarePosition();
            right_motor->tarePosition();
                
            if (left_motor->getActualVelocity() < 0 || right_motor->getActualVelocity() < 0) {
                left_motor->moveAbsolute(0, 1);
                right_motor->moveAbsolute(0, 1);
                // limit_timeout_bottom = 1000;
            }
        } else if (limit_timeout_bottom > 0) {
            limit_timeout_bottom--;
        }
>>>>>>> 67efc8548abcf0c84a783b690f36e23a620b6b04
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

    void Lift::raiseByOneCube() {
        // cout << "raise called" << endl;
        auto lift = Lift::getInstance();
        int diff = 206;
        lift->left_motor->moveAbsolute(lift->left_motor->getPosition() + diff, constants::LIFT_UP_VELOCITY);
        lift->right_motor->moveAbsolute(lift->right_motor->getPosition() + diff, constants::LIFT_UP_VELOCITY);
    }

    void Lift::lowerByOneCube() {
        // cout << "lower called" << endl;
        auto lift = Lift::getInstance();
        int diff = 206;
        lift->left_motor->moveAbsolute(lift->left_motor->getPosition() - diff, constants::LIFT_DOWN_VELOCITY);
        lift->right_motor->moveAbsolute(lift->right_motor->getPosition() - diff, constants::LIFT_DOWN_VELOCITY);
    }

    void Lift::printDebug() {
        cout << "[DEBUG][Lift] Left target: " << left_motor->getTargetPosition() << endl;
        cout << "[DEBUG][Lift] Right target: " << right_motor->getTargetPosition() << endl;
        cout << "[DEBUG][Lift] Left actual: " << left_motor->getPosition() << endl;
        cout << "[DEBUG][Lift] Right actual: " << right_motor->getPosition() << endl;
    }

    int Lift::printLCD(int line) {
        std::ostringstream out;

        out << "[L] lpos: " << left_motor->getPosition();
        out << ", rpos: " << right_motor->getPosition();
        out << ", tt: " << Lift::limit_timeout_top;
        out << ", bt: " << Lift::limit_timeout_bottom;

        pros::lcd::clear_line(line);
        pros::lcd::set_text(line, out.str());

        line++;
        out.clear();
        out.str("");

        out << "[C] lV: " << left_motor->getVoltage();
        out << ", rV: " << right_motor->getVoltage();

        line++;
        out.clear();
        out.str("");

        out << "[C] rT: " << right_motor->getTemperature();
        out << ", lT: " << left_motor->getTemperature();

        pros::lcd::clear_line(line);
        pros::lcd::set_text(line, out.str());

        return line;
    }

    void Lift::waitUntilSettled() {
        while (!(left_motor->isStopped() && right_motor->isStopped()))
            pros::delay(10);
    }

    void Lift::moveVoltageMax(int sign) {
        if (sign >= -1 && sign <= 1) {
            Lift::getInstance()->left_motor->moveVoltage(sign * constants::MOTOR_MAX_VOLTAGE);
            Lift::getInstance()->right_motor->moveVoltage(sign * constants::MOTOR_MAX_VOLTAGE);
        }
    }

    void Lift::move(std::int32_t velocity) {
        // (moving up while top limit switch is pressed) or (moving down while bottom limit switch is pressed)
        if ((velocity > 0 && top_limit_switch->isPressed()) || (velocity < 0 && bottom_limit_switch->isPressed())) {
            return;
        }

        left_motor->moveVelocity(velocity);
        right_motor->moveVelocity(velocity);
    }

    std::pair<int, int> Lift::getPosition() {
        return std::pair<int, int>(left_motor->getPosition(), right_motor->getPosition());
    }
}

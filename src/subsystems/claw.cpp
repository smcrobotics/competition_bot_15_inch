#include "smc/subsystems/claw.h"
#include "smc/util/util.h"
#include "smc/util/constants.h"

using std::cout;
using std::endl;

namespace claw {
    std::unique_ptr<okapi::Motor> claw_motor;
    ClawState clawState;

    void init() {
        claw_motor = util::initMotor(robot::CLAW_MOTOR_PORT, okapi::Motor::gearset::green);
        claw_motor->setBrakeMode(constants::OKAPI_BRAKE);
        claw_motor->moveVoltage(-12000);
        pros::delay(500);
        claw_motor->moveVoltage(0);
        claw_motor->tarePosition();
        clawState = ClawState::CLOSED;
    }

    void update() {}

    void setClawState(ClawState state) {
        if (state == ClawState::OPEN)
            // claw_motor->moveVoltage(12000);
            claw_motor->moveAbsolute(600, 200);
        else
            // claw_motor->moveVoltage(-12000);
            claw_motor->moveAbsolute(0, 200);

        clawState = state;
    }

    void moveClawToPosition(int position) {
        
    }


    void toggleClaw() {
        setClawState((ClawState) !clawState);
    }
}

namespace subsystems {
    Claw::Claw() {
        claw_motor = util::initMotor(robot::CLAW_MOTOR_PORT, okapi::Motor::gearset::green);
        claw_motor->setBrakeMode(constants::OKAPI_BRAKE);

        // Make sure claw is closed before we tare position
        claw_motor->moveVoltage(-12000);
        pros::delay(500);
        claw_motor->moveVoltage(0);

        claw_motor->tarePosition();
        clawState = ClawState::CLOSED;

    }

    Claw * Claw::getInstance() {
        static Claw claw;
        return &claw;
    }

    void Claw::update() {}

    void Claw::printDebug() {
        cout << "[DEBUG][Claw] Claw position target: " << claw_motor->getTargetPosition() << endl;
        cout << "[DEBUG][Claw] Claw position actual: " << claw_motor->getPosition() << endl;
        cout << "[DEBUG][Claw] Claw state: " << ((bool) clawState ? "Open" : "Closed") << endl;
    }

    void Claw::printLCD(int line) {
        std::ostringstream out;
        out << "[C] state: " << (bool) clawState;
        out << ", pos: " << claw_motor->getPosition();

        pros::lcd::clear_line(line);
        pros::lcd::set_text(line, out.str());
    }

    void Claw::setClawState(ClawState state) {
        if (state == ClawState::OPEN)
            claw_motor->moveAbsolute(robot::CLAW_MOTOR_POS_OPEN, 200);
        else
            claw_motor->moveAbsolute(robot::CLAW_MOTOR_POS_CLOSED, 200);

        clawState = state;
    }

    void Claw::toggleClaw() {
        auto claw = getInstance();
        claw->setClawState((ClawState) !((bool) claw->clawState));
    }
}
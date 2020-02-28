#include "smc/subsystems/claw.h"
#include "smc/util/util.h"
#include "smc/util/constants.h"

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
        clawState = ClawState::OPEN;
        claw_motor->moveAbsolute(600, 200);
    }

    void update() {}

    void setClawState(ClawState state) {
        if (state == ClawState::OPEN)
            // claw_motor->moveVoltage(12000);
            claw_motor->moveAbsolute(600, 200);
        else
            // claw_motor->moveVoltage(-12000);
            claw_motor->moveAbsolute(450, 200);

        clawState = state;
    }

    void moveClawToPosition(int position) {
        
    }

    int getPosition() {
        return claw_motor->getPosition();
    }

    void toggleClaw() {
        setClawState((ClawState) !clawState);
    }
}
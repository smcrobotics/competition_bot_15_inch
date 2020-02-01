#include "smc/subsystems/claw.h"
#include "smc/util/util.h"
#include "smc/util/constants.h"

namespace claw {
    std::unique_ptr<okapi::Motor> claw_motor;
    ClawState clawState;

    void init() {
        claw_motor = util::initMotor(robot::CLAW_MOTOR_PORT);
        claw_motor->tarePosition();
        clawState = ClawState::CLOSED;
    }

    void update() {}

    void setClawState(ClawState state) {
        if (state == ClawState::OPEN)
            claw_motor->moveVoltage(12000);
        else
            claw_motor->moveVoltage(-12000);

        clawState = state;
    }

    void printPos() {
        std::cout << claw_motor->getPosition() << std::endl;
    }

    void toggleClaw() {
        setClawState((ClawState) !clawState);
    }
}
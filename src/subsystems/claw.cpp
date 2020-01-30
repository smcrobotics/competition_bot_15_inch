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

    void setClawState(ClawState state) {
        if (state == ClawState::OPEN)
            claw_motor->moveAbsolute(robot::CLAW_MOTOR_POS_OPEN, 120);
        else
            claw_motor->moveAbsolute(robot::CLAW_MOTOR_POS_CLOSED, 120);

        clawState = state;
    }

    void toggleClaw() {
        setClawState((ClawState) !clawState);
    }
}
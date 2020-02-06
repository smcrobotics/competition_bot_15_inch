//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_TRAY_H
#define ROBOT_CODE_TRAY_H

#include "api.h"
#include "okapi/api.hpp"

namespace claw {
    enum ClawState { CLOSED = 0, OPEN = 1 };

    void init();
    void update();

    void setClawState(ClawState state);
    void toggleClaw();
    void printPos();

    extern ClawState clawState;
    extern std::unique_ptr<okapi::Motor> claw_motor;
}

#endif //ROBOT_CODE_TRAY_H

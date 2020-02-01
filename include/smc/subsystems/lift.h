//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_INTAKE_H
#define ROBOT_CODE_INTAKE_H

#include "api.h"
#include "okapi/api.hpp"

namespace lift {
    const std::int32_t UP_VELOCITY = 120;
    const std::int32_t DOWN_VELOCITY = 80;

    enum LiftPosition { UP, DOWN, TOWER_LOW, TOWER_MID, TOWER_HIGH };

    void init();

    void update();
    void printPos();

    void moveToPosition(LiftPosition position);
    void move(std::int32_t velocity);

    extern std::unique_ptr<okapi::Motor> left_lift_motor;
    extern std::unique_ptr<okapi::Motor> right_lift_motor;
}

#endif //ROBOT_CODE_INTAKE_H

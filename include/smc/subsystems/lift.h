//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_INTAKE_H
#define ROBOT_CODE_INTAKE_H

#include "api.h"
#include "okapi/api.hpp"

namespace lift {
    enum LiftPosition { UP, DOWN };

    void init();

    void update();
    void printPos();

    void moveToPosition(LiftPosition position);

    extern std::unique_ptr<okapi::Motor> left_lift_motor;
    extern std::unique_ptr<okapi::Motor> right_lift_motor;
}

#endif //ROBOT_CODE_INTAKE_H

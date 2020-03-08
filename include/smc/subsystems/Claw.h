//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_TRAY_H
#define ROBOT_CODE_TRAY_H

#include "api.h"
#include "okapi/api.hpp"
#include "smc/subsystems/AbstractSubsystem.h"

namespace subsystems {
class Claw : public AbstractSubsystem {
public:
    enum class ClawState { CLOSED = 0, OPEN = 1 };

    static Claw * getInstance();
    Claw(const Claw &) = delete;
    void operator=(const Claw & lhs) = delete;

    void update() override;
    void printDebug() override;
    int printLCD(int line) override;

    void setClawState(ClawState state);
    static void toggleClaw();

    void moveManual(int velocity);

private:
    Claw();

    ClawState clawState;
    std::unique_ptr<okapi::Motor> claw_motor;
};
}

#endif //ROBOT_CODE_TRAY_H

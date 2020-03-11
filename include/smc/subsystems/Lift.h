#ifndef ROBOT_CODE_LIFT_H
#define ROBOT_CODE_LIFT_H

#include "api.h"
#include "okapi/api.hpp"
#include "smc/subsystems/AbstractSubsystem.h"

namespace subsystems {
class Lift : public AbstractSubsystem {
    public:
        enum LiftPosition { UP, DOWN, TOWER_LOW, TOWER_MID, TOWER_HIGH };

        static Lift * getInstance();
        Lift(const Lift &) = delete;
        void operator=(const Lift & lhs) = delete;

        void update() override;
        void printDebug() override;
        int printLCD(int line) override;

        void moveToPosition(LiftPosition position);
        void waitUntilSettled();
        void move(std::int32_t velocity);

        static void togglePosition();

        static void moveVoltageMax(int sign);

    private:
        Lift();

        LiftPosition current_pos;
        int limit_timeout_bottom;
        int limit_timeout_top;
        bool did_tare_bottom;
        bool did_tare_top;

        std::unique_ptr<okapi::ADIButton> top_limit_switch;
        std::unique_ptr<okapi::ADIButton> bottom_limit_switch;
        std::unique_ptr<okapi::Motor> left_motor;
        std::unique_ptr<okapi::Motor> right_motor;
    };
}

#endif //ROBOT_CODE_LIFT_H

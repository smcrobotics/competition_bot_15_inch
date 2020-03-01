#include <unistd.h>
#define chdir f_chdir


#include "main.h"

#include "smc/robot.h"
#include "smc/util/Binding.h"

using namespace okapi;
using std::cout;
using std::endl;

typedef okapi::ControllerButton Button;

/* Begin forward declaration block */
std::shared_ptr<okapi::AsyncMotionProfileController> robot::profile_controller;
std::shared_ptr<okapi::ChassisController> robot::chassis;
/* End forward declaration block */


static bool on_right_side = true;
static bool update_lcd_info = true;

void on_right_button() {
    on_right_side = true;
    pros::lcd::clear_line(0);
    pros::lcd::set_text(0, "Auton: Right side");
}

void on_left_button() {
    on_right_side = false;
    pros::lcd::clear_line(0);
    pros::lcd::set_text(0, "Auton: Left side");
}

void on_center_button() {
    update_lcd_info = !update_lcd_info;
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();
    pros::lcd::register_btn0_cb(on_left_button);
    pros::lcd::register_btn2_cb(on_right_button);
    pros::lcd::register_btn1_cb(on_center_button);
    
    robot::chassis =
            ChassisControllerBuilder().withMotors(
                            okapi::MotorGroup{robot::FRONT_LEFT_DRIVE_MOTOR_PORT, robot::BACK_LEFT_DRIVE_MOTOR_PORT},
                            okapi::MotorGroup{robot::FRONT_RIGHT_DRIVE_MOTOR_PORT, robot::BACK_RIGHT_DRIVE_MOTOR_PORT})
                    .withDimensions(AbstractMotor::gearset::green, ChassisScales({4_in, 12.5_in}, okapi::imev5GreenTPR))
                    .build();

    lift::init();
    claw::init();
    sideIndicate::init();

    // limits: velocity, acceleration, jerk
    robot::profile_controller = okapi::AsyncMotionProfileControllerBuilder()
            .withLimits({0.3, 0.3, 0.3 })
            .withOutput(robot::chassis)
            .buildMotionProfileController();

    robot::profile_controller->generatePath({
                                                    {89_cm, 0_cm, 0_deg},
                                                    {0_in, 0_in, 0_deg}}, "forward"
    );

    robot::profile_controller->generatePath({{89_cm, 0_in, 0_deg},
                                                    {67_cm, 85_cm, -90_deg}}, "toCube" // Profile name
    );

    robot::profile_controller->generatePath({{67_cm, 85_cm, -90_deg},
                                             {4_cm, 91.5_cm, 0_deg}}, "toTower");

   // bool starts_on_red_side = sideIndicate::getSide();
   //  if (starts_on_red_side) {
   //      robot::profile_controller->generatePath({
   //          {0_ft, 0_in, 0_deg}}, "autonomous_path" // Profile name for red
   //      );
   //  } else {
   //      robot::profile_controller->generatePath({
   //          {0_ft, 0_in, 0_deg}}, "autonomous_path" // Profile name for blue
   //      );
   //  }
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


void autonomous() {
    /**
    sample routine 1: pick up cube and place it in a tower
    **/
    robot::chassis->getModel()->setBrakeMode(constants::OKAPI_BRAKE);

    robot::profile_controller->setTarget("forward");
    robot::profile_controller->waitUntilSettled();
    robot::profile_controller->setTarget("forward", true); // reverse back to initial position
    robot::profile_controller->waitUntilSettled();

    // drop claw
    lift::moveToPosition(lift::TOWER_LOW);
    pros::delay(1000);
    lift::moveToPosition(lift::DOWN);
    pros::delay(1000);
    claw::setClawState(claw::OPEN);
    // claw dropped

    bool starts_on_red_side = false; // if we start on red side, mirror the path
    robot::profile_controller->setTarget("toCube", false, starts_on_red_side);
    robot::profile_controller->waitUntilSettled();
    claw::setClawState(claw::CLOSED);

    // end push cube in

    robot::profile_controller->setTarget("toTower", false, starts_on_red_side);
    lift::moveToPosition(lift::TOWER_MID);
    robot::profile_controller->waitUntilSettled();
    claw::setClawState(claw::OPEN);
    
    robot::chassis->getModel()->setBrakeMode(constants::OKAPI_COAST);
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void initBindings(std::vector<Binding *> & bind_list) {
    // Claw binding
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::TOGGLE_CLAW),
            subsystems::Claw::toggleClaw, nullptr, nullptr));

    // Lift Position Up binding
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::LIFT_POS_UP), []() {
        lift::moveToPosition(lift::UP);
    }, nullptr, nullptr));

    // Lift Position Down binding
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::LIFT_POS_DOWN), []() {
        lift::moveToPosition(lift::DOWN);
    }, nullptr, nullptr));

    // Lift Position Tower Low binding
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::LIFT_POS_TOWER_LOW), []() {
        lift::moveToPosition(lift::TOWER_LOW);
    }, nullptr, nullptr));

    // Lift Position Tower Mid binding
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::LIFT_POS_TOWER_MID), []() {
        lift::moveToPosition(lift::TOWER_MID);
    }, nullptr, nullptr));

    // Lift Position Tower High binding
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::LIFT_POS_TOWER_HIGH), []() {
        lift::moveToPosition(lift::TOWER_HIGH);
    }, nullptr, nullptr));

    // Lift Move Up binding
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::LIFT_MOVE_UP), []() {
        lift::move(20);
    }, []() {
        lift::move(0);
    }, nullptr));

    // Lift Move Down binding
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::LIFT_MOVE_DOWN), []() {
        lift::move(-25);
    }, []() {
        lift::move(0);
    }, nullptr));

    // TODO: Remove this before competition
//    bind_list.emplace_back(new Binding(okapi::ControllerButton(okapi::ControllerDigital::L1), autonomous, nullptr, nullptr)); // Bind for auto test
    // Note: Au`to bind is blocking
    /** End bind block **/
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void opcontrol() {
    const bool DEBUG = false;
    bool isBrake = false;

    okapi::Controller master(okapi::ControllerId::master);

    std::vector<Binding *> bind_list;
    initBindings(bind_list);
    std::vector<subsystems::AbstractSubsystem *> systems;

    systems.push_back(subsystems::Claw::getInstance());

    // Have to do the drive-brake toggle here because it relies on variables local to main()
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::DRIVE_BRAKE_TOGGLE), nullptr,
                                       [isBrake, master]() mutable {
                                           isBrake = !isBrake;
                                           robot::chassis->getModel()->setBrakeMode(isBrake ? constants::OKAPI_BRAKE : constants::OKAPI_COAST);
                                           master.setText(0, 0, isBrake ? "Brake mode on " : "Brake mode off");
                                       }, nullptr));


    cout << "Initialization finished, entering drive loop" << endl;
    while (true) {
        drive::opControl(master);
        lift::printPos();

        lift::update();
        for (Binding * b : bind_list)
            b->update();

        int lcd_line = 1; // start debug info on line 1 an increment for each subsystem
        for (subsystems::AbstractSubsystem * system : systems) {
            system->update();

            if (update_lcd_info)
                system->printLCD(lcd_line);

            if (DEBUG)
                system->printDebug();

            lcd_line++;
        }

        pros::delay(1);
    }

    for (Binding * b : bind_list)
        delete b;

    cout << "Exiting opcontrol()" << endl;
}
#pragma clang diagnostic pop
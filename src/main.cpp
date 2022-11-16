#include "pros/rtos.hpp"
#include "pros/vision.hpp"

#include "Drivetrain.hpp"
#include "Flywheel.hpp"
#include "Robot.hpp"
#include "Intake.hpp"

#include "main.hpp"
#include "ports.hpp"

#include "odometry.hpp"
#include "Expansion.hpp"

#include "okapi/impl/device/motor/motor.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"

void initialize() {}
void disabled() {}
void competition_initialize() {}

void opcontrol() {
	Drivetrain const drivetrain{ ports::LEFT_BACK_MOTOR, ports::RIGHT_BACK_MOTOR, ports::LEFT_FRONT_MOTOR, ports::RIGHT_FRONT_MOTOR };
	Flywheel const flywheel{ ports::FLYWHEEL, ports::PISTON_INDEXER };
	Intake const intake{ ports::INTAKE_LEFT, ports::INTAKE_RIGHT };
	Expansion const expansion{ ports::EXPANSION_PISTON };
	Roller const roller { ports::ROLLER };
	Robot robot{ drivetrain, flywheel, intake, expansion, roller};

	while (true) {
		robot.update();
		pros::Task::delay(1);
	}
}

void autonomous() {
	auto odometry = build_odometry(okapi::MotorGroup({okapi::Motor(-ports::LEFT_BACK_MOTOR), okapi::Motor(-ports::LEFT_FRONT_MOTOR)}), 
								   okapi::MotorGroup({okapi::Motor(ports::RIGHT_BACK_MOTOR), okapi::Motor(ports::RIGHT_FRONT_MOTOR)}));
	odometry->turnAngle(90_deg);
	odometry->moveDistance(1_ft);
	odometry->turnAngle(90_deg);
	odometry->moveDistance(1_ft);
	odometry->turnAngle(90_deg);
	odometry->moveDistance(1_ft);
	odometry->turnAngle(90_deg);
	odometry->moveDistance(1_ft);
	odometry->turnAngle(90_deg);
}





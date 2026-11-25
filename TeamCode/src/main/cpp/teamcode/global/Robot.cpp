//
// Created by Sam on 11/13/2026.
//

#include "Robot.hpp"



void Robot::init()
{
    Robot::frontLeft = std::make_shared<DcMotorEx>("fl",
                                                   Constants::DRIVE_MOTOR_POWER_TOLERANCE);
    Robot::frontRight = std::make_shared<DcMotorEx>("fr",
                                                    Constants::DRIVE_MOTOR_POWER_TOLERANCE);
    Robot::backLeft = std::make_shared<DcMotorEx>("bl",
                                                  Constants::DRIVE_MOTOR_POWER_TOLERANCE);
    Robot::backRight = std::make_shared<DcMotorEx>("br",
                                                   Constants::DRIVE_MOTOR_POWER_TOLERANCE);
    frontLeft->setDirection(&DcMotorEx::Direction::FORWARD);
    frontRight->setDirection(&DcMotorEx::Direction::REVERSE);
    backLeft->setDirection(&DcMotorEx::Direction::FORWARD);
    backRight->setDirection(&DcMotorEx::Direction::REVERSE);


    Robot::robotChassis = std::make_shared<MecanumChassis>(frontLeft.get(), frontRight.get(),
                                                           backLeft.get(), backRight.get());
    Robot::robotChassis->toggleFloatMode();

    Robot::shooter = std::make_unique<DcMotorEx>("shooter", 0);
    Robot::shooter->setDirection(&DcMotorEx::Direction::REVERSE);

    Robot::intake = std::make_unique<DcMotorEx>("intake", 0);
    Robot::intake->setDirection(&DcMotorEx::Direction::REVERSE);

    Robot::stop = std::make_unique<Servo>("stop", 0);
    Robot::flowerLeft = std::make_unique<Servo>("flowerLeft", 0);
    Robot::flowerRight = std::make_unique<Servo>("flowerRight", 0);

    Robot::imu = std::make_unique<IMU>("imu");
    imu->initialize(Parameters::IMU::FacingDirection::RIGHT,
                    Parameters::IMU::FacingDirection::UP);
    //Robot::follower = std::make_unique<Follower>();


    Robot::otos = std::make_unique<SparkFunOTOS>("otos");
    otos->setAngularUnit(&AngleUnit::RADIANS);
    otos->setAngularScalar(1.0034);
    otos->setLinearUnit(&DistanceUnit::CM);
    otos->setLinearScalar(1);
    otos->setOffset(new Pose2D(-9.651, 0, 180));

    Robot::controlHub = std::make_unique<LynxModule>("Control Hub"); // Find Names
    Robot::expansionHub = std::make_unique<LynxModule>("Expansion Hub 2");
    controlHub->setBulkCachingMode(&LynxModule::BulkCachingMode::AUTO);
    expansionHub->setBulkCachingMode(&LynxModule::BulkCachingMode::AUTO);
}

void Robot::shutdown()
{
    robotChassis.reset();
    frontLeft.reset();
    frontRight.reset();
    backLeft.reset();
    backRight.reset();
    shooter.reset();
    intake.reset();
    stop.reset();
    flowerLeft.reset();
    flowerRight.reset();
    imu.reset();
    otos.reset();
    controlHub.reset();
    expansionHub.reset();
}

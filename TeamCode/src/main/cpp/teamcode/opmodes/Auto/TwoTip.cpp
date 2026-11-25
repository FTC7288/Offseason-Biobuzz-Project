#include "sdk/Sdk.h"
#include "lib/CustomLib.h"
#include "teamcode/global/Robot.hpp"

using namespace linearOpMode;
using namespace gamepads;
using namespace std::chrono;

enum State
{
    PRE_AUTO,
    FIRST_SHOOT,
    FIRST_INTERMEDIATE_POSE,
    FIRST_TURN_STATE,
    FLOWER_ONE_PICKUP,
    FLOWER_ONE_BACKUP,
    SECOND_TURN_STATE,
    SECOND_INTERMEDIATE_POSE,
    THIRD_TURN_STATE,
    BEFORE_LAUNCH_TWO,
    TOO_SECOND_SHOOT,
    SECOND_SHOOT,
    THIRD_INTERMEDIATE_POSE,
    FLOWER_TWO_PICKUP,
    FLOWER_TWO_BACKUP,
    THIRD_SHOOT,
    FIFTH_INTERMEDIATE_POSE,
    PARK_STATE,
    END_AUTO
};

extern "C" void TwoTip(JNIEnv* env, jobject thiz)
{
    initSDK(env, thiz);
    Robot::init();
    Robot::robotChassis->toggleBrakeMode();

    double prevTimeStep = 1;
    double shooterVelocity = 0;
    double shooterPower = 0;
    bool atSpeed = false;

    State state = PRE_AUTO;
    Joystick joystickOutput {0,0,0};

    constexpr double CM = 2.54;
    constexpr double PI = 3.14159;
    Pose2D startPose = Pose2D(88.0 * CM, 133.0 * CM,PI/2);
    Pose2D intermOnePose = Pose2D(126.28 * CM,91.33 * CM,PI/2);
    Pose2D flowerOnePose = Pose2D(132.74 * CM,91.37 * CM,0);
    Pose2D transferToSecondLaunchPose = Pose2D(110.02 * CM,21.44 * CM,0);
    Pose2D frontOfSecondLaunchPose = Pose2D(83 * CM,21.57 * CM,0);
    Pose2D secondLaunchPose = Pose2D(82.46 * CM,8.22 * CM,0);
    Pose2D flowerTwoPose = Pose2D(93.99 * CM,8.57 * CM,0);
    Pose2D otosEndPose {0, 0, 0};

    waitForStart();

    Robot::flowerLeft->setPosition(Robot::Constants::FLOWER_SERVO_LEFT_UP_POS);
    Robot::flowerRight->setPosition(Robot::Constants::FLOWER_SERVO_RIGHT_UP_POS);
    Robot::stop->setPosition(Robot::Constants::STOP_DOWN_POS);
    Robot::otos->setPosition(&startPose);
    Robot::otos->begin();
    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, Robot::otos->getPosition()->h};

    while (opModeIsActive())
    {
        telemetry::update();
        gamepads::update();

        auto time = steady_clock::now();
        double curTimeStep = duration<double,std::milli>(time.time_since_epoch()).count();

        double imuAngle = Robot::imu->getYawPitchRollAngles()->getYaw(AngleUnit::RADIANS);

        shooterVelocity = Robot::shooter->getVelocity();
        if (shooterVelocity < Robot::Constants::DESIRED_SHOOTER_VELOCITY - 10)
        {
            shooterPower = 1;
        } else if (shooterVelocity > Robot::Constants::DESIRED_SHOOTER_VELOCITY + 10)
        {
            shooterPower = 0;
        } else
        {
            atSpeed = true;
            shooterPower = 0;
        }

        telemetry::addData("IMU", std::to_string(imuAngle).c_str());
        telemetry::addData("X",std::to_string(Robot::otos->getPosition()->x).c_str());
        telemetry::addData("Y", std::to_string(Robot::otos->getPosition()->y).c_str());
        telemetry::addData("H", std::to_string(Robot::otos->getPosition()->h).c_str());



//        switch (state)
//        {
//            default:
//                Robot::robotChassis->driveFieldCentric(0, 0, 0, Robot::otos->getPosition()->h);
//                break;
//            case PRE_AUTO:
//                prevTimeStep = curTimeStep;
//                state = FIRST_SHOOT;
//                break;
//            case FIRST_SHOOT:
//                joystickOutput = Robot::robotChassis->straightLineFollower(otosEndPose, intermOnePose);
//                Robot::robotChassis->driveFieldCentric(joystickOutput.stickY / 1.75, joystickOutput.stickX / 1.75, 0, Robot::otos->getPosition()->h);
//
//                if ((Robot::otos->getPosition()->x < intermOnePose.x + 10 && Robot::otos->getPosition()->x > intermOnePose.x - 10) && (Robot::otos->getPosition()->y < intermOnePose.y + 5 && Robot::otos->getPosition()->y > intermOnePose.y - 5))
//                {
//                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, Robot::otos->getPosition()->h};
//                    state = FIRST_INTERMEDIATE_POSE;
//                }
//                break;
//        };




        switch (state)
        {
            default:
                break;
            case PRE_AUTO:
                prevTimeStep = curTimeStep;
                state = FIRST_SHOOT;
                break;
            case FIRST_SHOOT:
                Robot::shooter->setPower(shooterPower);
                if (atSpeed)
                {
                    Robot::stop->setPosition(Robot::Constants::STOP_DOWN_POS);
                    Robot::intake->setPower(Robot::Constants::INTAKE_POWER);
                }
                if (curTimeStep - prevTimeStep > 4000)
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    atSpeed = false;
                    prevTimeStep = curTimeStep;
                    state = FIRST_INTERMEDIATE_POSE;
                }
                break;
            case FIRST_INTERMEDIATE_POSE:
                Robot::shooter->setPower(0);
                Robot::stop->setPosition(Robot::Constants::STOP_UP_POS);
                Robot::intake->setPower(Robot::Constants::INTAKE_OFF_POWER);
                Robot::flowerLeft->setPosition(Robot::Constants::FLOWER_SERVO_LEFT_DOWN_POS);
                Robot::flowerRight->setPosition(Robot::Constants::FLOWER_SERVO_RIGHT_DOWN_POS);

                joystickOutput = Robot::robotChassis->straightLineFollower(otosEndPose, intermOnePose);
                Robot::robotChassis->driveRobotCentric(joystickOutput.stickY/1.75 , joystickOutput.stickX /1.75, 0);

                if (curTimeStep - prevTimeStep > 1250)
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = FIRST_TURN_STATE;
                }
                break;
            case FIRST_TURN_STATE:
                Robot::robotChassis->driveRobotCentric(0, 0, -0.7);
                if (curTimeStep - prevTimeStep > 400)
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = FLOWER_ONE_PICKUP;
                }
                break;
            case FLOWER_ONE_PICKUP:

                Robot::intake->setPower(Robot::Constants::INTAKE_POWER);
                joystickOutput = Robot::robotChassis->straightLineFollower(otosEndPose, flowerOnePose);

                Robot::robotChassis->driveRobotCentric(-joystickOutput.stickY / 2, -joystickOutput.stickX / 2, 0);
                if (curTimeStep - prevTimeStep > 2000)
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = FLOWER_ONE_BACKUP;
                }
                break;
            case FLOWER_ONE_BACKUP:
                joystickOutput = Robot::robotChassis->straightLineFollower(otosEndPose, intermOnePose);
                Robot::robotChassis->driveRobotCentric(joystickOutput.stickY / 2, joystickOutput.stickX / 2, 0);
                if (curTimeStep - prevTimeStep > 250) // TUNE TIME
                {
                    prevTimeStep = curTimeStep;
                    state = SECOND_TURN_STATE;
                }
                break;
            case SECOND_TURN_STATE:
                Robot::robotChassis->driveRobotCentric(0, 0, 0.65);
                if (curTimeStep - prevTimeStep > 420) // TUNE TIME
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = SECOND_INTERMEDIATE_POSE;
                }
                break;
            case SECOND_INTERMEDIATE_POSE:
                Robot::intake->setPower(Robot::Constants::INTAKE_OFF_POWER);
                Robot::flowerLeft->setPosition(Robot::Constants::FLOWER_SERVO_LEFT_UP_POS);
                Robot::flowerRight->setPosition(Robot::Constants::FLOWER_SERVO_RIGHT_UP_POS);

                joystickOutput = Robot::robotChassis->straightLineFollower(otosEndPose, transferToSecondLaunchPose);
                Robot::robotChassis->driveRobotCentric(joystickOutput.stickY / 1.75, joystickOutput.stickX / 1.75, 0);

                if (curTimeStep - prevTimeStep > 1500) // TUNE TIME
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = THIRD_TURN_STATE;
                }
                break;
            case THIRD_TURN_STATE:
                Robot::robotChassis->driveRobotCentric(0, 0, 0.65);
                if (curTimeStep - prevTimeStep > 900) // TUNE TIME
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = BEFORE_LAUNCH_TWO;
                }
                break;
            case BEFORE_LAUNCH_TWO:
                Robot::robotChassis->driveRobotCentric(0, -0.5, 0);
                if (curTimeStep - prevTimeStep > 1100) // TUNE TIME
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = TOO_SECOND_SHOOT;
                }
                break;
            case TOO_SECOND_SHOOT:
                Robot::robotChassis->driveRobotCentric(-0.5, 0, 0);
                if (curTimeStep - prevTimeStep > 500) // TUNE TIME
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = SECOND_SHOOT;
                }
                break;
            case SECOND_SHOOT:
                Robot::robotChassis->driveRobotCentric(0, 0, 0);
                Robot::shooter->setPower(shooterPower);
                if (atSpeed)
                {
                    Robot::stop->setPosition(Robot::Constants::STOP_DOWN_POS);
                    Robot::intake->setPower(Robot::Constants::INTAKE_POWER);
                }
                if (curTimeStep - prevTimeStep > 4000)
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = THIRD_INTERMEDIATE_POSE;
                }
                break;
            case THIRD_INTERMEDIATE_POSE:
                Robot::shooter->setPower(0);
                Robot::stop->setPosition(Robot::Constants::STOP_UP_POS);
                Robot::flowerRight->setPosition(Robot::Constants::FLOWER_SERVO_RIGHT_DOWN_POS);
                Robot::flowerLeft->setPosition(Robot::Constants::FLOWER_SERVO_RIGHT_DOWN_POS);

                Robot::robotChassis->driveRobotCentric(0.939, 0.342, 0);
                if (curTimeStep - prevTimeStep > 300)
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = FLOWER_TWO_PICKUP;
                }
                break;
            case FLOWER_TWO_PICKUP:
                Robot::robotChassis->driveRobotCentric(-0.5, 0, 0);
                if (curTimeStep - prevTimeStep > 2000)
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = FLOWER_TWO_BACKUP;
                }
                break;
            case FLOWER_TWO_BACKUP:
                Robot::flowerRight->setPosition(Robot::Constants::FLOWER_SERVO_RIGHT_UP_POS);
                Robot::flowerLeft->setPosition(Robot::Constants::FLOWER_SERVO_RIGHT_UP_POS);
                Robot::robotChassis->driveRobotCentric(0.940, -0.324, 0);
                if (curTimeStep - prevTimeStep > 300)
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    prevTimeStep = curTimeStep;
                    state = END_AUTO;
                }
                break;
            case END_AUTO:
                Robot::robotChassis->driveRobotCentric(0, 0, 0);
                break;
        }

    }

    Robot::shutdown();
    clearSDK(env);
}

//A utonomous(TwoTip, dummy)


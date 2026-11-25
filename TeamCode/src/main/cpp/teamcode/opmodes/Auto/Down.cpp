#include "sdk/Sdk.h"
#include "lib/CustomLib.h"
#include "teamcode/global/Robot.hpp"

using namespace linearOpMode;
using namespace gamepads;
using namespace std::chrono;

extern "C" void Down(JNIEnv* env, jobject thiz)
{
    initSDK(env, thiz);
    Robot::init();
    Robot::robotChassis->toggleBrakeMode();

    double prevTimeStep = 1;
    double shooterVelocity = 0;
    double shooterPower = 0;
    bool atSpeed = false;

    uint8_t state = 0;
    Joystick joystickOutput {0,0,0};

    constexpr double CM = 2.54;
    Pose2D startPose = Pose2D(87.2 * CM, 133.3 * CM,0);
    Pose2D intermPose = Pose2D(86.96 * CM,117.81 * CM,0);
    Pose2D goalPose = Pose2D(44.33 * CM,141.98 * CM,0);
    Pose2D otosEndPose {0, 0, 0};

    waitForStart();

    Robot::stop->setPosition(Robot::Constants::STOP_DOWN_POS);
    Robot::otos->setPosition(&startPose);
    Robot::otos->begin();

    while (opModeIsActive())
    {
        telemetry::update();
        gamepads::update();
        auto time = steady_clock::now();
        double curTimeStep = duration<double,std::milli>(time.time_since_epoch()).count();
        telemetry::addData("Time Step", std::to_string(curTimeStep - prevTimeStep).c_str());
        telemetry::addData("State", std::to_string(state).c_str());

        telemetry::addData("Y", std::to_string(gamepad1->left_stick_y).c_str());
        telemetry::addData("X", std::to_string(-gamepad1->left_stick_x).c_str());
        telemetry::addData("X Right", std::to_string(-gamepad1->right_stick_x).c_str());


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

        switch (state)
        {
            default:
                break;
            case 0:
                prevTimeStep = curTimeStep;
                state++;
                break;
            case 1:
                if (curTimeStep - prevTimeStep > 18000)
                {
                    prevTimeStep = curTimeStep;
                    state++;
                }
                break;
            case 2:
                Robot::shooter->setPower(shooterPower);
                if (atSpeed)
                {
                    Robot::stop->setPosition(Robot::Constants::STOP_DOWN_POS);
                    Robot::intake->setPower(Robot::Constants::INTAKE_POWER);
                }
                if (curTimeStep - prevTimeStep > 5000)
                {
                    atSpeed = false;
                    prevTimeStep = curTimeStep;
                    state++;
                }
                break;
            case 3:
                Robot::shooter->setPower(0);
                Robot::stop->setPosition(Robot::Constants::STOP_UP_POS);
                Robot::intake->setPower(Robot::Constants::INTAKE_OFF_POWER);

                joystickOutput = Robot::robotChassis->straightLineFollower(startPose, intermPose);
                Robot::robotChassis->driveRobotCentric(joystickOutput.stickY /1.75, joystickOutput.stickX/1.75, joystickOutput.stickRotation);

                if (curTimeStep - prevTimeStep > 275)
                {
                    otosEndPose = {Robot::otos->getPosition()->x, Robot::otos->getPosition()->y, 0};
                    atSpeed = false;
                    prevTimeStep = curTimeStep;
                    state++;
                }
                break;
            case 4:
                if (curTimeStep - prevTimeStep > 200)
                {
                    prevTimeStep = curTimeStep;
                    state++;
                }
                break;
            case 5:
                joystickOutput = Robot::robotChassis->straightLineFollower(otosEndPose, goalPose);
                Robot::robotChassis->driveRobotCentric(joystickOutput.stickY, joystickOutput.stickX, joystickOutput.stickRotation);
                if (curTimeStep - prevTimeStep > 1000)
                {
                    prevTimeStep = curTimeStep;
                    state++;
                }
                break;
            case 6:
                Robot::robotChassis->driveRobotCentric(0,0,0);
                break;
        }
    }

    Robot::shutdown();
    clearSDK(env);
}

Autonomous(Down, dummy)

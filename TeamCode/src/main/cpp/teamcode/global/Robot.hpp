#include "sdk/Sdk.h"
#include "lib/CustomLib.h"

namespace Robot
{
    namespace Constants
    {
        constexpr double DESIRED_SHOOTER_VELOCITY = 1180;
        constexpr double DRIVE_MOTOR_POWER_TOLERANCE = 0.05;
        constexpr double STOP_DOWN_POS = 0.4;
        constexpr double STOP_UP_POS = 0.75;
        constexpr double INTAKE_POWER = 1;
        constexpr double OUTTAKE_POWER = -1;
        constexpr double INTAKE_OFF_POWER = 0;
        constexpr double FLOWER_SERVO_RIGHT_DOWN_POS = 0.191;
        constexpr double FLOWER_SERVO_LEFT_DOWN_POS = 0.809;
        constexpr double FLOWER_SERVO_RIGHT_UP_POS = 0.98;
        constexpr double FLOWER_SERVO_LEFT_UP_POS = 0.02;

    }

    inline std::shared_ptr<DcMotorEx> frontLeft = nullptr;
    inline std::shared_ptr<DcMotorEx> frontRight = nullptr;
    inline std::shared_ptr<DcMotorEx> backLeft = nullptr;
    inline std::shared_ptr<DcMotorEx> backRight = nullptr;
    inline std::unique_ptr<DcMotorEx> shooter = nullptr;
    inline std::unique_ptr<DcMotorEx> intake = nullptr;
    inline std::unique_ptr<Servo> stop = nullptr;
    inline std::unique_ptr<Servo> flowerLeft = nullptr;
    inline std::unique_ptr<Servo> flowerRight = nullptr;
    inline std::unique_ptr<IMU> imu = nullptr;
    inline std::unique_ptr<SparkFunOTOS> otos = nullptr;
    inline std::unique_ptr<LynxModule> controlHub = nullptr;
    inline std::unique_ptr<LynxModule> expansionHub = nullptr;

    inline std::shared_ptr<MecanumChassis> robotChassis = nullptr;

    //inline std::unique_ptr<Follower> follower = nullptr;

    void init();
    void shutdown();
}

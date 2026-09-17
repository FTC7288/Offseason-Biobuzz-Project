#include "sdk/Sdk.h"

using namespace linearOpMode;
using namespace gamepads;

extern "C" void MainExperiment(JNIEnv* env, jobject thiz)
{
    initSDK(env, &thiz);

    std::unique_ptr<LynxModule> controlHub = std::make_unique<LynxModule>("Control Hub");
    controlHub->setBulkCachingMode(LynxModule::BulkCachingMode::AUTO);

    std::unique_ptr<LynxModule> expansionHub = std::make_unique<LynxModule>("Expansion Hub");
    expansionHub->setBulkCachingMode(LynxModule::BulkCachingMode::AUTO);

    std::unique_ptr<IMU> imu = std::make_unique<IMU>("imu");
    imu->initialize(Parameters::IMU::FacingDirection::RIGHT, Parameters::IMU::FacingDirection::UP);

    waitForStart();

    while(opModeIsActive())
    {

    }

}

TeleOp(MainExperiment, dummy)
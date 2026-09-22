#include "sdk/util/Util.h"
#include "sdk/headers/navigation/Pose2D.h"
#include "sdk/headers/navigation/AngleUnit.h"
#include "sdk/headers/navigation/DistanceUnit.h"



class SparkFunOTOS
{
private:
    jobject sparksFunOtos = nullptr;

    jmethodID beginID = nullptr;
    jmethodID setOffsetID = nullptr;
    jmethodID getPositionID = nullptr;
    jmethodID setPositionID = nullptr;
    jmethodID setAngularUnitID = nullptr;
    jmethodID setLinearUnitID = nullptr;
    jmethodID setAngularScalarID = nullptr;
    jmethodID setLinearScalarID = nullptr;

public:
    inline static jclass sparksFunOtosClazz = nullptr;

    explicit SparkFunOTOS(const char* name);

    ~SparkFunOTOS();

    bool begin();

    void setOffset(Pose2D *pose);

    void setPosition(Pose2D *pose);

    Pose2D* getPosition();

    void setAngularUnit(jobject *angleUnit);

    void setLinearUnit(jobject *distanceUnit);

    bool setAngularScalar(double scalar);

    bool setLinearScalar(double scalar);
};

#pragma once

#include "sdk/util/Util.h"

class Gamepad
{
private:
    jobject gamepad = nullptr;

    jmethodID rumbleID = nullptr;

    jfieldID aID = nullptr;
    jfieldID bID = nullptr;
    jfieldID xID = nullptr;
    jfieldID yID = nullptr;
    jfieldID backID = nullptr;
    jfieldID startID = nullptr;
    jfieldID dpad_downID = nullptr;
    jfieldID dpad_upID = nullptr;
    jfieldID dpad_leftID = nullptr;
    jfieldID dpad_rightID = nullptr;
    jfieldID left_bumperID = nullptr;
    jfieldID right_bumperID = nullptr;
    jfieldID left_stick_buttonID = nullptr;
    jfieldID right_stick_buttonID = nullptr;


    jfieldID left_triggerID = nullptr;
    jfieldID right_triggerID = nullptr;

    jfieldID left_stick_xID = nullptr;
    jfieldID left_stick_yID = nullptr;
    jfieldID right_stick_xID = nullptr;
    jfieldID right_stick_yID = nullptr;

public:
    inline static jclass gamepadClazz = nullptr;


    bool a = false;
    bool b = false;
    bool x = false;
    bool y = false;
    bool back = false;
    bool start = false;
    bool dpad_down = false;
    bool dpad_up = false;
    bool dpad_left = false;
    bool dpad_right = false;
    bool left_bumper = false;
    bool right_bumper = false;
    bool left_stick_button = false;
    bool right_stick_button = false;

    float left_trigger = 0;
    float right_trigger = 0;
    float left_stick_x = 0;
    float left_stick_y = 0;
    float right_stick_x = 0;
    float right_stick_y = 0;

    explicit Gamepad(const jobject& gamepad);

    ~Gamepad();

    void update();

    void rumble(const int& durationMillis);

    bool leftTriggerDown() const;

    bool rightTriggerDown() const;
};

namespace gamepads
{
    extern std::unique_ptr<Gamepad> gamepad1;
    extern std::unique_ptr<Gamepad> gamepad2;

    void update();

}
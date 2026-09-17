#include "sdk/headers/hardware/Gamepad.h"


Gamepad::Gamepad(const jobject& jgamepad) : gamepad(jgamepad) {
    JNIEnv* env = getEnv();

    if (gamepadClazz == nullptr)
    {
        LOG_ERROR("-------------------------- gamepadClazz == nullptr -----------------------------");
    }

    if (gamepad == nullptr)
    {
        LOG_ERROR("-------------------------- gamepad object == nullptr -----------------------------");
    }


    rumbleID = env->GetMethodID(gamepadClazz, "rumble", "(I)V");

    aID = env->GetFieldID(gamepadClazz, "a", "Z");
    bID = env->GetFieldID(gamepadClazz, "b", "Z");
    xID = env->GetFieldID(gamepadClazz, "x", "Z");
    yID = env->GetFieldID(gamepadClazz, "y", "Z");
    startID = env->GetFieldID(gamepadClazz, "start", "Z");
    backID = env->GetFieldID(gamepadClazz, "back", "Z");
    dpad_downID = env->GetFieldID(gamepadClazz, "dpad_down", "Z");
    dpad_upID = env->GetFieldID(gamepadClazz, "dpad_up", "Z");
    dpad_leftID = env->GetFieldID(gamepadClazz, "dpad_left", "Z");
    dpad_rightID = env->GetFieldID(gamepadClazz, "dpad_right", "Z");
    left_bumperID = env->GetFieldID(gamepadClazz, "left_bumper", "Z");
    right_bumperID = env->GetFieldID(gamepadClazz, "right_bumper", "Z");
    left_stick_buttonID = env->GetFieldID(gamepadClazz, "left_stick_button", "Z");
    right_stick_buttonID = env->GetFieldID(gamepadClazz, "right_stick_button", "Z");

    left_triggerID = env->GetFieldID(gamepadClazz, "left_trigger", "F");
    right_triggerID = env->GetFieldID(gamepadClazz, "right_trigger", "F");
    left_stick_xID = env->GetFieldID(gamepadClazz, "left_stick_x", "F");
    left_stick_yID = env->GetFieldID(gamepadClazz, "left_stick_y", "F");
    right_stick_xID = env->GetFieldID(gamepadClazz, "right_stick_x", "F");
    right_stick_yID = env->GetFieldID(gamepadClazz, "right_stick_y", "F");
}

Gamepad::~Gamepad()
{
    JNIEnv* env = getEnv();

    if (gamepadClazz)
    {
        env->DeleteGlobalRef(gamepadClazz);
        gamepadClazz = nullptr;
    }
    if (gamepad)
    {
        env->DeleteLocalRef(gamepad);
        gamepad = nullptr;
    }
}

void Gamepad::update() {
    JNIEnv* env = getEnv();

    if (aID == nullptr)
    {
        LOG_ERROR(" _______________ aID null ____________________");
    }

    a = env->GetBooleanField(gamepad, aID);
    b = env->GetBooleanField(gamepad, bID);
    x = env->GetBooleanField(gamepad, xID);
    y = env->GetBooleanField(gamepad, yID);
    start = env->GetBooleanField(gamepad, startID);
    back = env->GetBooleanField(gamepad, backID);
    dpad_down = env->GetBooleanField(gamepad, dpad_downID);
    dpad_up = env->GetBooleanField(gamepad, dpad_upID);
    dpad_left = env->GetBooleanField(gamepad, dpad_leftID);
    dpad_right = env->GetBooleanField(gamepad, dpad_rightID);
    left_bumper = env->GetBooleanField(gamepad, left_bumperID);
    right_bumper = env->GetBooleanField(gamepad, right_bumperID);
    left_stick_button = env->GetBooleanField(gamepad, left_stick_buttonID);
    right_stick_button = env->GetBooleanField(gamepad, right_stick_buttonID);

    left_trigger = env->GetFloatField(gamepad, left_triggerID);
    right_trigger = env->GetFloatField(gamepad, right_triggerID);
    left_stick_x = env->GetFloatField(gamepad, left_stick_xID);
    left_stick_y = env->GetFloatField(gamepad, left_stick_yID);
    right_stick_x = env->GetFloatField(gamepad, right_stick_xID);
    right_stick_y = env->GetFloatField(gamepad, right_stick_yID);
}

void Gamepad::rumble(const int &durationMillis) {
    JNIEnv* env = getEnv();
    env->CallVoidMethod(gamepad, rumbleID, durationMillis);
}


bool Gamepad::leftTriggerDown() const {
    return left_trigger > 0.5;
}

bool Gamepad::rightTriggerDown() const {
    return right_trigger > 0.5;
}


namespace gamepads
{
    std::unique_ptr<Gamepad> gamepad1 = nullptr;
    std::unique_ptr<Gamepad> gamepad2 = nullptr;


    void update()
    {
        gamepad1->update();
        gamepad2->update();
    }
}


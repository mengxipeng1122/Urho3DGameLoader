
#pragma once 

#include "../Global.h"

enum class InputKey
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    START,
    SELECT,
    FIRE_A,
    FIRE_B,
    FIRE_C,
    FIRE_D,
    FIRE_E,
    FIRE_F,

    SETTING,
    NUMS_KEY,
};


namespace Urho3D
{

URHO3D_EVENT(E_INPUTKEYDOWN,   InputKeyDown)
{
    URHO3D_PARAM(P_INPUTKEY,    InputKey);
    URHO3D_PARAM(P_INDEX,       Index);
}

URHO3D_EVENT(E_INPUTKEYUP,   InputKeyUp)
{
    URHO3D_PARAM(P_INPUTKEY,    InputKey);
    URHO3D_PARAM(P_INDEX,       Index);
}

}


namespace Urho3D
{

class InputSystem: public Object
{
    URHO3D_OBJECT(InputSystem, Object);

    public:
        InputSystem(Context* context);
        bool GetKeyState(InputKey key, int inputIdx);

    private:
        bool ConvertKeyToInputKey(VariantMap& eventData, InputKey& inputKey, int& inputIdx);
        bool ConvertJoystickToInputKey(VariantMap& eventData, InputKey& inputKey);

        void HandleKeyDown(StringHash eventType, VariantMap& eventData);
        void HandleKeyUp(StringHash eventType, VariantMap& eventData);

        constexpr static auto NUMS_KEY = static_cast<int>(InputKey::NUMS_KEY);
        constexpr static auto NUMS_IDX = 2;
        std::array<bool, NUMS_KEY*NUMS_IDX> keyStates_;
};

}


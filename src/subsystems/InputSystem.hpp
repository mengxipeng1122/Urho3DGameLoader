
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
};

using namespace Urho3D;
class InputSystem: public Object
{
    URHO3D_OBJECT(InputSystem, Object);

    public:
        InputSystem(Context* context): Object(context){}
        bool HasInputKey(VariantMap& eventData, InputKey& inputKey, int& inputIdx);
};


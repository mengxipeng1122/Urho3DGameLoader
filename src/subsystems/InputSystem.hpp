
#pragma once 

#include "../Global.h"

enum class InputKey
{
    UP_1P,
    DOWN_1P,
    LEFT_1P,
    RIGHT_1P,
    START_1P,
    SELECT_1P,
    FIRE_A_1P,
    FIRE_B_1P,
    FIRE_C_1P,
    FIRE_D_1P,
    FIRE_E_1P,
    FIRE_F_1P,

    UP_2P,
    DOWN_2P,
    LEFT_2P,
    RIGHT_2P,
    START_2P,
    SELECT_2P,
    FIRE_A_2P,
    FIRE_B_2P,
    FIRE_C_2P,
    FIRE_D_2P,
    FIRE_E_2P,
    FIRE_F_2P,
    
    SETTING,
};

using namespace Urho3D;
class InputSystem: public Object
{
    URHO3D_OBJECT(InputSystem, Object);

    public:
        InputSystem(Context* context): Object(context){}
        bool HasInputKey(VariantMap& eventData, InputKey& inputKey);
};


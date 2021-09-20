
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

    NUMS_KEY,
    
    SETTING=NUMS_KEY,
};

using namespace Urho3D;
class InputSystem: public Object
{
    URHO3D_OBJECT(InputSystem, Object);

    public:
        InputSystem(Context* context);
        bool KeyHasInputKey(VariantMap& eventData, InputKey& inputKey, int& inputIdx);
        bool JoystickButtonDownHasInputKey(VariantMap& eventData, InputKey& inputKey, int& inputIdx);
        void HandleKeyDown(StringHash eventType, VariantMap& eventData);
};


namespace {
    struct _A
    {
        _A(){
            g_allSubsystemRegisterFuns.Push([](Context* context){
                context->RegisterSubsystem(new InputSystem(context));
                });
            }
        ~_A(){}
    }_a;
    };

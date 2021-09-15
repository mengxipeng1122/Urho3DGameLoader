
#include <Urho3D/Input/InputEvents.h>

#include "InputSystem.hpp"

bool InputSystem::HasInputKey(VariantMap& eventData, InputKey& inputKey, int& inputIdx)
{
    using namespace KeyDown;
    int key = eventData[P_KEY].GetInt();

    switch(key)
    {
        case KEY_A:     { inputKey = InputKey::LEFT;   inputIdx=0; return true;}
        case KEY_D:     { inputKey = InputKey::RIGHT;  inputIdx=0; return true;}
        case KEY_W:     { inputKey = InputKey::UP;     inputIdx=0; return true;}
        case KEY_S:     { inputKey = InputKey::DOWN;   inputIdx=0; return true;}
        case KEY_1:     { inputKey = InputKey::START;  inputIdx=0; return true;}
        case KEY_2:     { inputKey = InputKey::SELECT; inputIdx=0; return true;}
        case KEY_I:     { inputKey = InputKey::FIRE_A; inputIdx=0; return true;}
        case KEY_O:     { inputKey = InputKey::FIRE_B; inputIdx=0; return true;}
        case KEY_K:     { inputKey = InputKey::FIRE_C; inputIdx=0; return true;}
        case KEY_L:     { inputKey = InputKey::FIRE_D; inputIdx=0; return true;}
        case KEY_U:     { inputKey = InputKey::FIRE_E; inputIdx=0; return true;}
        case KEY_J:     { inputKey = InputKey::FIRE_F; inputIdx=0; return true;}

        case KEY_LEFT:  { inputKey = InputKey::LEFT;   inputIdx=1; return true;}
        case KEY_RIGHT: { inputKey = InputKey::RIGHT;  inputIdx=1; return true;}
        case KEY_UP:    { inputKey = InputKey::UP;     inputIdx=1; return true;}
        case KEY_DOWN:  { inputKey = InputKey::DOWN;   inputIdx=1; return true;}
        case KEY_3:     { inputKey = InputKey::START;  inputIdx=1; return true;}
        case KEY_4:     { inputKey = InputKey::SELECT; inputIdx=1; return true;}
        case KEY_Z:     { inputKey = InputKey::FIRE_A; inputIdx=1; return true;}
        case KEY_X:     { inputKey = InputKey::FIRE_B; inputIdx=1; return true;}
        case KEY_C:     { inputKey = InputKey::FIRE_C; inputIdx=1; return true;}
        case KEY_V:     { inputKey = InputKey::FIRE_D; inputIdx=1; return true;}
        case KEY_B:     { inputKey = InputKey::FIRE_E; inputIdx=1; return true;}
        case KEY_N:     { inputKey = InputKey::FIRE_F; inputIdx=1; return true;}
        case KEY_9:     { inputKey = InputKey::SETTING;inputIdx=0; return true;} 
        default: return false;
    }
}


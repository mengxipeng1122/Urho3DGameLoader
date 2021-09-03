
#include <Urho3D/Input/InputEvents.h>

#include "InputSystem.hpp"

bool HasInputKey(VariantMap& eventData, InputKey& inputKey)
{
    using namespace KeyDown;
    int key = eventData[P_KEY].GetInt();

    switch(key)
    {
        case KEY_A:     { inputKey = InputKey::LEFT_1P;  return true;}
        case KEY_D:     { inputKey = InputKey::RIGHT_1P; return true;}
        case KEY_W:     { inputKey = InputKey::UP_1P;    return true;}
        case KEY_S:     { inputKey = InputKey::DOWN_1P;  return true;}
        case KEY_1:     { inputKey = InputKey::START_1P; return true;}
        case KEY_2:     { inputKey = InputKey::SELECT_1P;return true;}
        case KEY_I:     { inputKey = InputKey::FIRE_A_1P;return true;}
        case KEY_O:     { inputKey = InputKey::FIRE_B_1P;return true;}
        case KEY_K:     { inputKey = InputKey::FIRE_C_1P;return true;}
        case KEY_L:     { inputKey = InputKey::FIRE_D_1P;return true;}
        case KEY_U:     { inputKey = InputKey::FIRE_E_1P;return true;}
        case KEY_J:     { inputKey = InputKey::FIRE_F_1P;return true;}

        case KEY_LEFT:  { inputKey = InputKey::LEFT_2P;  return true;}
        case KEY_RIGHT: { inputKey = InputKey::RIGHT_2P; return true;}
        case KEY_UP:    { inputKey = InputKey::UP_2P;    return true;}
        case KEY_DOWN:  { inputKey = InputKey::DOWN_2P;  return true;}
        case KEY_3:     { inputKey = InputKey::START_2P; return true;}
        case KEY_4:     { inputKey = InputKey::SELECT_2P;return true;}
        case KEY_Z:     { inputKey = InputKey::FIRE_A_2P;return true;}
        case KEY_X:     { inputKey = InputKey::FIRE_B_2P;return true;}
        case KEY_C:     { inputKey = InputKey::FIRE_C_2P;return true;}
        case KEY_V:     { inputKey = InputKey::FIRE_D_2P;return true;}
        case KEY_B:     { inputKey = InputKey::FIRE_E_2P;return true;}
        case KEY_N:     { inputKey = InputKey::FIRE_F_2P;return true;}
        case KEY_9:     { inputKey = InputKey::SETTING;  return true;}
        default: return false;
    }
}

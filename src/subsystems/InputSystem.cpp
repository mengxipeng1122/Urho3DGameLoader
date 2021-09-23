
#include "../utils/log.hpp"
#include "InputSystem.hpp"

using namespace Urho3D;

InputSystem::InputSystem(Context* context)
    : Object(context)
{
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(InputSystem, HandleKeyDown));
    SubscribeToEvent(E_KEYUP,   URHO3D_HANDLER(InputSystem, HandleKeyUp));
    for(auto& k : keyStates_) k = false;
}

bool InputSystem::ConvertKeyToInputKey(VariantMap& eventData, InputKey& inputKey, int& inputIdx)
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

bool InputSystem::ConvertJoystickToInputKey(VariantMap& eventData, InputKey& inputKey)
{
    using namespace JoystickButtonDown;
    int key = eventData[P_BUTTON].GetInt();

    switch(key)
    {
        case 10:        { inputKey = InputKey::LEFT;   return true;}
        case 11:        { inputKey = InputKey::RIGHT;  return true;}
        case 8:         { inputKey = InputKey::UP;     return true;}
        case 9:         { inputKey = InputKey::DOWN;   return true;}
        case 6:         { inputKey = InputKey::START;  return true;}
        case 7:         { inputKey = InputKey::SELECT; return true;}
        case 0:         { inputKey = InputKey::FIRE_A; return true;}
        case 1:         { inputKey = InputKey::FIRE_B; return true;}
        case 2:         { inputKey = InputKey::FIRE_C; return true;}
        case 3:         { inputKey = InputKey::FIRE_D; return true;}
        case 4:         { inputKey = InputKey::FIRE_E; return true;}
        case 5:         { inputKey = InputKey::FIRE_F; return true;}

        default: return false;
    }
}

void InputSystem::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

    InputKey inputKey;
    int      inputIdx;

    if(ConvertKeyToInputKey(eventData, inputKey, inputIdx))
    {
        auto keyidx  = static_cast<int>(inputKey)+inputIdx*NUMS_KEY;
        keyStates_[keyidx] =true;
        VariantMap& eventData   = GetEventDataMap();
        auto key = static_cast<int>(inputKey);
        eventData[Urho3D::InputKeyDown::P_INPUTKEY]   = key;
        eventData[Urho3D::InputKeyDown::P_INDEX]      = inputIdx;
        SendEvent(E_INPUTKEYDOWN, eventData);
    }
}

void InputSystem::HandleKeyUp(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyUp;

    InputKey inputKey;
    int      inputIdx;


    if(ConvertKeyToInputKey(eventData, inputKey, inputIdx))
    {
        auto keyidx  = static_cast<int>(inputKey)+inputIdx*NUMS_KEY;
        keyStates_[keyidx] =false;
        using namespace InputKeyUp;
        VariantMap& eventData = GetEventDataMap();
        eventData[P_INPUTKEY]    = static_cast<int>(inputKey);
        eventData[P_INDEX]    = inputIdx;
        SendEvent(E_INPUTKEYUP, eventData);
    }
}

bool InputSystem::GetKeyState(InputKey key, int inputIdx)
{
    auto keyidx  = static_cast<int>(key)+inputIdx*NUMS_KEY;
    return keyStates_[keyidx];
}



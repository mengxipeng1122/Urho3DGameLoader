
#include "Screen.hpp"

void Screen::Enter()
{
    {
        String fileName= ToString("screens/%s.xml", "ScreenBase");
        SharedPtr<File> file = CACHE->GetFile(fileName); 
        UI_ROOT->LoadXML(*file);
    }
    {
        SubscribeToEvent(E_INPUTKEYDOWN, URHO3D_HANDLER(Screen, HandleInputKeyDown));
        SubscribeToEvent(E_INPUTKEYUP,   URHO3D_HANDLER(Screen, HandleInputKeyUp));
    }
}

void Screen::Leave()
{
    auto* uiRoot= context_->GetSubsystem<UI>()->GetRoot();
    uiRoot->RemoveAllChildren();
}

void Screen::HandleInputKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace InputKeyDown;
    auto key = static_cast<InputKey>(eventData[P_INPUTKEY].GetInt());
    auto idx =                      (eventData[P_INDEX].GetInt());
    HandleKeyDown(key, idx);
}

void Screen::HandleInputKeyUp(StringHash eventType, VariantMap& eventData)
{
    using namespace InputKeyUp;
    auto key = static_cast<InputKey>(eventData[P_INPUTKEY].GetInt());
    auto idx =                      (eventData[P_INDEX].GetInt());
    HandleKeyUp(key, idx);
}


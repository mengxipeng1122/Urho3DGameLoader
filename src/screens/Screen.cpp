
#include "../utils/log.hpp"
#include "Screen.hpp"

void Screen::Enter()
{
    {
        String fileName= ToString("screens/%s.xml", "ScreenBase");
        SharedPtr<File> file = CACHE->GetFile(fileName); 
        UI_ROOT->LoadXML(*file);
        if(HAS_DEBUG) {
            UI_ROOT->CreateChild<DEBUG_UIELEMENT_TYPE>(DEBUG_UIELEMENT_NAME);
        }
    }
    {
        SubscribeToEvent(E_INPUTKEYDOWN, URHO3D_HANDLER(Screen, HandleInputKeyDown));
        SubscribeToEvent(E_INPUTKEYUP,   URHO3D_HANDLER(Screen, HandleInputKeyUp));
    }
}

void Screen::Leave()
{
    {
        UnsubscribeFromEvent(E_INPUTKEYDOWN);
        UnsubscribeFromEvent(E_INPUTKEYUP);
    }
    auto* uiRoot= context_->GetSubsystem<UI>()->GetRoot();
    uiRoot->RemoveAllChildren();
}

void Screen::HandleInputKeyDown(StringHash eventType, VariantMap& eventData)
{
    auto key = (eventData[Urho3D::InputKeyDown::P_INPUTKEY].GetInt());
    auto idx = (eventData[Urho3D::InputKeyDown::P_INDEX].GetInt());
    auto inputkey = static_cast<InputKey>(key);
    HandleKeyDown(inputkey, idx);
}

void Screen::HandleInputKeyUp(StringHash eventType, VariantMap& eventData)
{
    using namespace InputKeyUp;
    auto key = static_cast<InputKey>(eventData[P_INPUTKEY].GetInt());
    auto idx =                      (eventData[P_INDEX].GetInt());
    HandleKeyUp(key, idx);
}

void Screen::InitAllUIElements()
{
    allUIElements_.Clear();
    const auto* screen = UI_ROOT->GetChildStaticCast<UIElement>(String("Screen"));
    if(screen!=nullptr) {
        for(const auto& ele : screen->GetChildren()) { 
            LOG_INFOS_CPP(ele); 
            WeakPtr<UIElement> element{ele};
            allUIElements_.Push(element);
        }
    }
    UpdataDebugElment();
}

bool Screen::HandleKeyDown(InputKey key, int idx)
{
    if(HAS_DEBUG) {
        auto inputSystem = INPUT_SYSTEM;
        if(inputSystem->GetKeyState(InputKey::FIRE_A,0))
        {
            auto position = allUIElements_[currentDebugUIElementIdx_]->GetPosition();
            switch (key) {
                case InputKey::UP       :{if(position.y_>0) position.y_--; } break;
                case InputKey::DOWN     :{                  position.y_++; } break;
                case InputKey::LEFT     :{if(position.x_>0) position.x_--; } break;
                case InputKey::RIGHT    :{                  position.x_++; } break;
            }
            allUIElements_[currentDebugUIElementIdx_]->SetPosition(position);
        }
        if(key == InputKey::FIRE_B){
            currentDebugUIElementIdx_++; 
            currentDebugUIElementIdx_%=allUIElements_.Size(); 
        }
        UpdataDebugElment();
    }
    return false;
}

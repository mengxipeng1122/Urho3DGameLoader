
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
    LOG_INFOS_CPP("name ",allUIElements_[currentDebugUIElementIdx_]->GetName());
}

bool Screen::HandleKeyDown(InputKey key, int idx)
{
    auto handled=false;
    if(HAS_DEBUG) {
        auto inputSystem = INPUT_SYSTEM;
        if(inputSystem->GetKeyState(InputKey::FIRE_A,0)) {
            auto position = allUIElements_[currentDebugUIElementIdx_]->GetPosition();
            switch (key) {
                case InputKey::UP       :{if(position.y_>0) position.y_--; handled=true;} break;
                case InputKey::DOWN     :{                  position.y_++; handled=true;} break;
                case InputKey::LEFT     :{if(position.x_>0) position.x_--; handled=true;} break;
                case InputKey::RIGHT    :{                  position.x_++; handled=true;} break;
            }
            allUIElements_[currentDebugUIElementIdx_]->SetPosition(position);
        }

        if(inputSystem->GetKeyState(InputKey::FIRE_C,0)) {
            auto size = allUIElements_[currentDebugUIElementIdx_]->GetSize();
            switch (key) {
                case InputKey::UP       :{if(size.y_>0) size.y_--; handled=true;} break;
                case InputKey::DOWN     :{              size.y_++; handled=true;} break;
                case InputKey::LEFT     :{if(size.x_>0) size.x_--; handled=true;} break;
                case InputKey::RIGHT    :{              size.x_++; handled=true;} break;
            }
            allUIElements_[currentDebugUIElementIdx_]->SetSize(size);
        }

        if(inputSystem->GetKeyState(InputKey::FIRE_A,0)) {
            if(key == InputKey::FIRE_B){
                currentDebugUIElementIdx_++; 
                currentDebugUIElementIdx_%=allUIElements_.Size(); 
                LOG_INFOS_CPP("name ",allUIElements_[currentDebugUIElementIdx_]->GetName());
                handled = true;
            }
        }
        UpdataDebugElment();
    }
    return handled;
}


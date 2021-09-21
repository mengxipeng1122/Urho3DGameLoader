
#include "IOTestScreen.hpp"
#include "../widgets/TextSelectMenuItem.hpp"
#include "../widgets/ImageSelectMenuItem.hpp"

void IOTestScreen::Enter()
{
    Screen::Enter();
    Screen::LoadScreen(ToString("screens/%s.xml", GetName()));
    const auto* screen = UI_ROOT->GetChildStaticCast<UIElement>(String("Screen"));

    joystickDir1p_ = screen->GetChildStaticCast<JoystickDir>(String("Joysick Dir 1P"));
    joystickSelect1p_ = screen->GetChildStaticCast<JoystickKey>(String("Select 1P"));
    joystickStart1p_  = screen->GetChildStaticCast<JoystickKey>(String("Start 1P"));
    joystickA1p_  = screen->GetChildStaticCast<JoystickKey>(String("A 1P"));
    joystickB1p_  = screen->GetChildStaticCast<JoystickKey>(String("B 1P"));
    joystickC1p_  = screen->GetChildStaticCast<JoystickKey>(String("C 1P"));
    joystickD1p_  = screen->GetChildStaticCast<JoystickKey>(String("D 1P"));
    joystickE1p_  = screen->GetChildStaticCast<JoystickKey>(String("E 1P"));
    joystickF1p_  = screen->GetChildStaticCast<JoystickKey>(String("F 1P"));

    joystickDir2p_ = screen->GetChildStaticCast<JoystickDir>(String("Joysick Dir 2P"));
    joystickSelect2p_ = screen->GetChildStaticCast<JoystickKey>(String("Select 2P"));
    joystickStart2p_  = screen->GetChildStaticCast<JoystickKey>(String("Start 2P"));
    joystickA2p_  = screen->GetChildStaticCast<JoystickKey>(String("A 2P"));
    joystickB2p_  = screen->GetChildStaticCast<JoystickKey>(String("B 2P"));
    joystickC2p_  = screen->GetChildStaticCast<JoystickKey>(String("C 2P"));
    joystickD2p_  = screen->GetChildStaticCast<JoystickKey>(String("D 2P"));
    joystickE2p_  = screen->GetChildStaticCast<JoystickKey>(String("E 2P"));
    joystickF2p_  = screen->GetChildStaticCast<JoystickKey>(String("F 2P"));

    InitAllUIElements();

}

void IOTestScreen::Leave()
{
    Screen::Leave();
}

bool IOTestScreen::HandleKeyDown(InputKey key, int idx)
{
    Screen::HandleKeyDown(key, idx);
    if(idx>=2) return false;
    if(key >=InputKey::NUMS_KEY) return false;

    UpdateWidget();
    return true;
}

bool IOTestScreen::HandleKeyUp(InputKey key, int idx)
{
    if(idx>=2) return false;
    if(key >=InputKey::NUMS_KEY) return false;

    UpdateWidget();
    return true;
}

void IOTestScreen::UpdateJoystick(WeakPtr<JoystickDir>& widget, int idx)
{
    ASSERT_CPP(idx<2, "idx not correct ", idx);
    ASSERT_CPP(widget!=nullptr, "widget is nullptr");

    auto numsKey = static_cast<int>(InputKey::NUMS_KEY);
    auto inputSystem = INPUT_SYSTEM;
    auto upHolding      = inputSystem->GetKeyState(InputKey::UP,    idx);
    auto downHolding    = inputSystem->GetKeyState(InputKey::DOWN,  idx);
    auto leftHolding    = inputSystem->GetKeyState(InputKey::LEFT,  idx);
    auto rightHolding   = inputSystem->GetKeyState(InputKey::RIGHT, idx);

    // 1p 
    widget->SetState(JoystickDir::State::CENTER);
    if(    upHolding && leftHolding) {
        widget->SetState(JoystickDir::State::UP_LEFT);
    }
    else if( upHolding && rightHolding) {
        widget->SetState(JoystickDir::State::UP_RIGHT);
    }
    else if( downHolding && leftHolding) {
        widget->SetState(JoystickDir::State::DOWN_LEFT);
    }
    else if( downHolding && rightHolding) {
        widget->SetState(JoystickDir::State::DOWN_RIGHT);
    }
    else if(upHolding) {
        widget->SetState(JoystickDir::State::UP);
    }
    else if(downHolding) {
        widget->SetState(JoystickDir::State::DOWN);
    }
    else if(leftHolding) {
        widget->SetState(JoystickDir::State::LEFT);
    }
    else if(rightHolding) {
        widget->SetState(JoystickDir::State::RIGHT);
    }
}

void IOTestScreen::UpdateWidget()
{

    UpdateJoystick(joystickDir1p_, 0);
    UpdateJoystick(joystickDir2p_, 1);

    auto numsKey = static_cast<int>(InputKey::NUMS_KEY);
    auto inputSystem = INPUT_SYSTEM;
    joystickSelect1p_->SetState(inputSystem->GetKeyState(InputKey::SELECT, 0));
    joystickStart1p_ ->SetState(inputSystem->GetKeyState(InputKey::START , 0));
    joystickA1p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_A, 0));
    joystickB1p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_B, 0));
    joystickC1p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_C, 0));
    joystickD1p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_D, 0));
    joystickE1p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_E, 0));
    joystickF1p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_F, 0));

    joystickSelect2p_->SetState(inputSystem->GetKeyState(InputKey::SELECT, 1));
    joystickStart2p_ ->SetState(inputSystem->GetKeyState(InputKey::START , 1));
    joystickA2p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_A, 1));
    joystickB2p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_B, 1));
    joystickC2p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_C, 1));
    joystickD2p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_D, 1));
    joystickE2p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_E, 1));
    joystickF2p_     ->SetState(inputSystem->GetKeyState(InputKey::FIRE_F, 1));
}



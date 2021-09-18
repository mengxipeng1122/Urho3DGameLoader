
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


}

void IOTestScreen::Leave()
{
    Screen::Leave();
}

bool IOTestScreen::HandleKeyDown(InputKey key, int idx)
{
    if(idx>=2) return false;
    if(key >=InputKey::NUMS_KEY) return false;

    auto kidx = static_cast<int>(InputKey::NUMS_KEY)*idx+ static_cast<int>(key);
    keysIsHolding_[kidx] = true; 
    UpdateWidget();
    return true;
}

bool IOTestScreen::HandleKeyUp(InputKey key, int idx)
{
    if(idx>=2) return false;
    if(key >=InputKey::NUMS_KEY) return false;

    auto kidx = static_cast<int>(InputKey::NUMS_KEY)*idx+ static_cast<int>(key);
    keysIsHolding_[kidx] = false;
    UpdateWidget();
    return true;
}

void IOTestScreen::UpdateJoystick(WeakPtr<JoystickDir>& widget, int idx)
{
    ASSERT_CPP(idx<2, "idx not correct ", idx);
    ASSERT_CPP(widget!=nullptr, "widget is nullptr");

    auto numsKey = static_cast<int>(InputKey::NUMS_KEY);

    // 1p 
    widget->SetState(JoystickDir::State::CENTER);
    if(    keysIsHolding_[static_cast<int>(InputKey::UP) +numsKey*idx]
        && keysIsHolding_[static_cast<int>(InputKey::LEFT) +numsKey*idx])
    {
        widget->SetState(JoystickDir::State::UP_LEFT);
    }
    else if(    keysIsHolding_[static_cast<int>(InputKey::UP) +numsKey*idx]
        && keysIsHolding_[static_cast<int>(InputKey::RIGHT) +numsKey*idx])
    {
        widget->SetState(JoystickDir::State::UP_RIGHT);
    }
    else if(    keysIsHolding_[static_cast<int>(InputKey::DOWN) +numsKey*idx]
        && keysIsHolding_[static_cast<int>(InputKey::LEFT) +numsKey*idx])
    {
        widget->SetState(JoystickDir::State::DOWN_LEFT);
    }
    else if(    keysIsHolding_[static_cast<int>(InputKey::DOWN) +numsKey*idx]
        && keysIsHolding_[static_cast<int>(InputKey::RIGHT) +numsKey*idx])
    {
        widget->SetState(JoystickDir::State::DOWN_RIGHT);
    }
    else if(keysIsHolding_[static_cast<int>(InputKey::UP) +numsKey*idx])
    {
        widget->SetState(JoystickDir::State::UP);
    }
    else if(keysIsHolding_[static_cast<int>(InputKey::DOWN) +numsKey*idx])
    {
        widget->SetState(JoystickDir::State::DOWN);
    }
    else if(keysIsHolding_[static_cast<int>(InputKey::LEFT) +numsKey*idx])
    {
        widget->SetState(JoystickDir::State::LEFT);
    }
    else if(keysIsHolding_[static_cast<int>(InputKey::RIGHT) +numsKey*idx])
    {
        widget->SetState(JoystickDir::State::RIGHT);
    }

}

void IOTestScreen::UpdateWidget()
{

    UpdateJoystick(joystickDir1p_, 0);
    UpdateJoystick(joystickDir2p_, 1);

    auto numsKey = static_cast<int>(InputKey::NUMS_KEY);
    joystickSelect1p_->SetState(keysIsHolding_[static_cast<int>(InputKey::SELECT) +numsKey*0]);
    joystickStart1p_ ->SetState(keysIsHolding_[static_cast<int>(InputKey::START ) +numsKey*0]);
    joystickA1p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_A) +numsKey*0]);
    joystickB1p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_B) +numsKey*0]);
    joystickC1p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_C) +numsKey*0]);
    joystickD1p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_D) +numsKey*0]);
    joystickE1p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_E) +numsKey*0]);
    joystickF1p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_F) +numsKey*0]);

    joystickSelect2p_->SetState(keysIsHolding_[static_cast<int>(InputKey::SELECT) +numsKey*1]);
    joystickStart2p_ ->SetState(keysIsHolding_[static_cast<int>(InputKey::START ) +numsKey*1]);
    joystickA2p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_A) +numsKey*1]);
    joystickB2p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_B) +numsKey*1]);
    joystickC2p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_C) +numsKey*1]);
    joystickD2p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_D) +numsKey*1]);
    joystickE2p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_E) +numsKey*1]);
    joystickF2p_     ->SetState(keysIsHolding_[static_cast<int>(InputKey::FIRE_F) +numsKey*1]);
}



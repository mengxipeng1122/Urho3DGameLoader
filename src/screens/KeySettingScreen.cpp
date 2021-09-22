
#include "KeySettingScreen.hpp"
#include "SettingsScreen.hpp"
#include "../widgets/TextSelectMenuItem.hpp"
#include "../widgets/ImageSelectMenuItem.hpp"

void KeySettingScreen::Enter()
{
    Screen::Enter();
    Screen::LoadScreen(ToString("screens/%s.xml", GetName()));
    const auto* screen = UI_ROOT->GetChildStaticCast<UIElement>(String("Screen"));

    Screen::InitAllUIElements();
}

void KeySettingScreen::Leave()
{
    Screen::Leave();
}

bool KeySettingScreen::HandleKeyDown(InputKey key, int idx)
{
    Screen::HandleKeyDown(key, idx);
    return false;
}

bool KeySettingScreen::HandleKeyUp(InputKey key, int idx)
{
    Screen::HandleKeyUp(key, idx);
    return false;
}



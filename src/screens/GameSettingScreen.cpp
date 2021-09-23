
#include "GameSettingScreen.hpp"
#include "SettingsScreen.hpp"
#include "../widgets/TextSelectMenuItem.hpp"
#include "../widgets/ImageSelectMenuItem.hpp"

void GameSettingScreen::Enter()
{
    Screen::Enter();
    Screen::LoadScreen(ToString("screens/%s.xml", GetName()));
    Screen::InitAllUIElements();
    const auto* screen = UI_ROOT->GetChildStaticCast<UIElement>(String("Screen"));



}

void GameSettingScreen::Leave()
{
    Screen::Leave();
}

bool GameSettingScreen::HandleKeyDown(InputKey key, int idx)
{
    Screen::HandleKeyDown(key, idx);
    return false;
}

bool GameSettingScreen::HandleKeyUp(InputKey key, int idx)
{
    Screen::HandleKeyUp(key, idx);
    return false;
}





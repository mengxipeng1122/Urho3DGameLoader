
#include "WifiScreen.hpp"
#include "SettingsScreen.hpp"
#include "../widgets/TextSelectMenuItem.hpp"
#include "../widgets/ImageSelectMenuItem.hpp"

void WifiScreen::Enter()
{
    Screen::Enter();
    Screen::LoadScreen(ToString("screens/%s.xml", GetName()));
    InitAllUIElements();

    const auto* screen = UI_ROOT->GetChildStaticCast<UIElement>(String("Screen"));

    scanWifiWorker_.Run();

}

void WifiScreen::Leave()
{
    scanWifiWorker_.Stop();
    Screen::Leave();
}

bool WifiScreen::HandleKeyDown(InputKey key, int idx)
{
    Screen::HandleKeyDown(key, idx);
    return true;
}

bool WifiScreen::HandleKeyUp(InputKey key, int idx)
{
    return false;
}




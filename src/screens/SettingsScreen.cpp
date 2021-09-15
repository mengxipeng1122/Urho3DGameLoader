
#include "SettingsScreen.hpp"

void SettingsScreen::Enter()
{

    Screen::Enter();
    auto* uiRoot= context_->GetSubsystem<UI>()->GetRoot();
    auto* screen = uiRoot->CreateChild<UIElement>(GetName());
    auto* cache = context_->GetSubsystem<ResourceCache>(); 
    String fileName= ToString("screens/%s.xml", GetName());
    SharedPtr<File> file = cache->GetFile(fileName); 
    screen->LoadXML(*file);
}

void SettingsScreen::Leave()
{
    Screen::Leave();
}

bool SettingsScreen::HandleKeyDown(InputKey key, int idx)
{
    return false;
}


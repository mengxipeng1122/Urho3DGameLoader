
#include "Screen.hpp"

void Screen::Enter()
{
    {
        String fileName= ToString("screens/%s.xml", "ScreenBase");
        SharedPtr<File> file = CACHE->GetFile(fileName); 
        UI_ROOT->LoadXML(*file);
    }
}

void Screen::Leave()
{
    auto* uiRoot= context_->GetSubsystem<UI>()->GetRoot();
    uiRoot->RemoveAllChildren();
}

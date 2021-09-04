
#include "Screen.hpp"

void Screen::Enter()
{
    auto* cache = context_->GetSubsystem<ResourceCache>(); 
    auto* uiRoot= context_->GetSubsystem<UI>()->GetRoot();
    String fileName= ToString("screens/%s.xml", "ScreenBase");
    SharedPtr<File> file = cache->GetFile(fileName); uiRoot->LoadXML(*file);
}

void Screen::Leave()
{
    auto* uiRoot= context_->GetSubsystem<UI>()->GetRoot();
    uiRoot->RemoveAllChildren();
}

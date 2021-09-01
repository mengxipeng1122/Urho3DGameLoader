

#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/Resource/ResourceCache.h>

#include "IOTestScreen.hpp"

using namespace Urho3D;

void IOTestScreen::Enter(Context* context)
{
    Screen::Enter(context);
    auto* uiRoot= context->GetSubsystem<UI>()->GetRoot();
    auto* screen = uiRoot->CreateChild<UIElement>(GetName());
    auto* cache = context->GetSubsystem<ResourceCache>(); 
    String fileName= ToString("screens/%s.xml", GetName());
    SharedPtr<File> file = cache->GetFile(fileName); 
    screen->LoadXML(*file);

}

void IOTestScreen::Leave(Context* context)
{
    Screen::Leave(context);
}

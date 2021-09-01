

#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/Resource/ResourceCache.h>

#include "IOTestScreen.hpp"

using namespace Urho3D;

void IOTestScreen::Enter(Context* context)
{
    auto* cache = context->GetSubsystem<ResourceCache>(); 
    auto* uiRoot= context->GetSubsystem<UI>()->GetRoot();

    String fileName= ToString("screens/%s.xml", GetName());

    SharedPtr<File> file = cache->GetFile(fileName); uiRoot->LoadXML(*file);
}

void IOTestScreen::Leave(Context* context)
{
}

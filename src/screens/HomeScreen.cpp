
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/Resource/ResourceCache.h>

#include "HomeScreen.hpp"

using namespace Urho3D;

void HomeScreen::Enter(Context* context)
{
    Screen::Enter(context);
    auto* uiRoot= context->GetSubsystem<UI>()->GetRoot();
    auto* screen = uiRoot->CreateChild<UIElement>(GetName());
    auto* cache = context->GetSubsystem<ResourceCache>(); 
    String fileName= ToString("screens/%s.xml", GetName());
    SharedPtr<File> file = cache->GetFile(fileName); 
    screen->LoadXML(*file);

    // add text
//    auto* text = screen->CreateChild<Text>();
//    text->SetText("HOME");
//    text->SetFont(cache->GetResource<Font>("res/geometr415.ttf"), 35);
//    //text->SetMinWidth(CeilToInt(text->GetRowWidth(0) + 10));
//    text->SetPosition(15,15);
}

void HomeScreen::Leave(Context* context)
{
    Screen::Leave(context);
}

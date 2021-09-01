
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/Localization.h>

#include "../widgets/PageIndicator.hpp"
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

    auto* tipHome = screen->GetChild(String("tipHome"));
    ASSERT_CPP(tipHome!=nullptr, " can not found tipHome ");

//    auto* pageIndicator = screen->CreateChild<PageIndicator>("pageIndicator");

    ////auto* pageIndicator = static_cast<PageIndicator*>(screen->GetChild(String("pageIndicator")));
    for(auto& c : screen->GetChildren())
    {
        LOG_INFOS_CPP(" c ", c->GetName().CString());
    }
  //  auto* pageIndicator = screen->GetChild(String("pageIndicator"));
  //  ASSERT_CPP(pageIndicator!=nullptr, " can not found pageIndicator ");

    //pageIndicator->Update();



}

void HomeScreen::Leave(Context* context)
{
    Screen::Leave(context);
}


#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/Input/InputEvents.h>
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

    pageIndicator_ = static_cast<PageIndicator*>(screen->GetChild(String("pageIndicator")));
    ASSERT_CPP(pageIndicator_!=nullptr, " can not found pageIndicator ");

}

void HomeScreen::Leave(Context* context)
{
    Screen::Leave(context);
}

bool HomeScreen::HandleKeyDown(Context* context, StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;
    int key = eventData[P_KEY].GetInt();
    if(key =='2')
    {
        static auto page = 100;
        static auto tpage = 100;
        ASSERT_CPP(pageIndicator_!=nullptr, " can not found pageIndicator ");
        pageIndicator_->SetPage(page, tpage);
        page+=1;
        tpage+=100;
        return true;
    }
    return false;
}

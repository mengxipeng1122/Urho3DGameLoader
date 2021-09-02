
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/Localization.h>

#include "../widgets/PageIndicator.hpp"
#include "../widgets/TabSelector.hpp"
#include "HomeScreen.hpp"

using namespace Urho3D;

void HomeScreen::Enter()
{
    Screen::Enter();
    auto* uiRoot= context_->GetSubsystem<UI>()->GetRoot();
    auto* screen = uiRoot->CreateChild<UIElement>(GetName());
    auto* cache = context_->GetSubsystem<ResourceCache>(); 
    String fileName= ToString("screens/%s.xml", GetName());
    SharedPtr<File> file = cache->GetFile(fileName); 
    screen->LoadXML(*file);

    auto* tipHome = screen->GetChild(String("tipHome"));
    ASSERT_CPP(tipHome!=nullptr, " can not found tipHome ");

    pageIndicator_ = static_cast<PageIndicator*>(screen->GetChild(String("pageIndicator")));
    ASSERT_CPP(pageIndicator_!=nullptr, " can not found pageIndicator ");

    mainTab_ = static_cast<TabSelector*>(screen->GetChild(String("Main Tab")));
    ASSERT_CPP(mainTab_!=nullptr, " can not found Main Tab");

    SubscribeToEvent(mainTab_, E_TABCHANGED, URHO3D_HANDLER(HomeScreen, HandleTabChanged));

}

void HomeScreen::Leave()
{
    LOG_INFOS_CPP(" go here ");
    UnsubscribeFromEvent(mainTab_, E_TABCHANGED);
    Screen::Leave();
}

bool HomeScreen::HandleKeyDown( StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

    ASSERT_CPP(mainTab_!=nullptr, " can not found Main Tab");
    bool success = mainTab_->HandleKeyDown(eventType, eventData);
    if(success) return true;

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

void HomeScreen::HandleTabChanged(StringHash eventType, VariantMap& eventData)
{
    LOG_INFOS_CPP(" go here ");
}

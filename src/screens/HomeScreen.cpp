


#include "HomeScreen.hpp"


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
    mainTab_->SetSelected(true);
    mainTab_->Update();


    gamelist_ = screen->GetChildStaticCast<Gamelist>(String("Gamelist"));
    ASSERT_CPP(gamelist_!=nullptr, " can not found Gamelist");

    SetGamelist();

}

void HomeScreen::Leave()
{
    LOG_INFOS_CPP(" go here ");
    UnsubscribeFromEvent(mainTab_, E_TABCHANGED);
    Screen::Leave();
}

bool HomeScreen::HandleKeyDown( InputKey key)
{
    using namespace KeyDown;
    ASSERT_CPP(mainTab_!=nullptr, " can not found Main Tab");
    ASSERT_CPP(gamelist_!=nullptr, " can not found Main Tab");

    {
        if (mainTab_->IsSelected() && key == InputKey::DOWN_1P)
        {
            mainTab_->SetSelected(false); mainTab_->Update();
            gamelist_->SetSelected(true); gamelist_->Update();
        }
        else if(gamelist_->IsSelected() && key == InputKey::START_1P)
        {
            mainTab_->SetSelected(true); mainTab_->Update();
            gamelist_->SetSelected(false); gamelist_->Update();
        }
    }

    if(mainTab_->IsSelected())
    {
        bool success = mainTab_->HandleKeyDown(key);
        if(success) return true;
    }
    else if(gamelist_->IsSelected())
    {
        bool success = gamelist_->HandleKeyDown(key);
        if(success) return true;
    }

    return false;
}

void HomeScreen::HandleTabChanged(StringHash eventType, VariantMap& eventData)
{
    LOG_INFOS_CPP(" go here ");
}

void HomeScreen::SetGamelist()
{

    auto* cache = context_->GetSubsystem<ResourceCache>(); 
    auto* jgamelist = cache->GetResource<JSONFile>("gamelist1.json");
    auto  gamelist = jgamelist->GetRoot().GetArray();
    Gamelist::Item item;
    for(auto& game : gamelist)
    {
        auto thumbnailPath = game.Get("thumbnailPath").GetString();
        auto name = game.Get("name").GetString();
        item.thumbnailPath_ = thumbnailPath;
        item.name_ = name;
        gamelist_->addItem(item);
    }
    gamelist_->Update();
}


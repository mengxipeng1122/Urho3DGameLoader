


#include "HomeScreen.hpp"
#include "../widgets/VideoPlayer.hpp"
#include "../components/VideoPlayerComponent.hpp"


VideoPlayerComponent* tvc{nullptr};
void HomeScreen::Enter()
{
	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(HomeScreen, HandleUpdate));
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
    SubscribeToEvent(gamelist_, E_ITEMCHANGED, URHO3D_HANDLER(HomeScreen, HandleGamelistChanged));

    SetGamelist();

    videoPlayer_ = screen->GetChildStaticCast<VideoPlayer>(String("VideoPlayer"));

}

void HomeScreen::Leave()
{
    LOG_INFOS_CPP(" go here ");
    UnsubscribeFromEvent(mainTab_, E_TABCHANGED);
    UnsubscribeFromEvent(this, E_UPDATE);
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
            return true;
        }
        else if(gamelist_->IsSelected() && key == InputKey::START_1P)
        {
            mainTab_->SetSelected(true); mainTab_->Update();
            gamelist_->SetSelected(false); gamelist_->Update();
            return true;
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
//    LOG_INFOS_CPP(" go here ");
//    if( mainTab_->GetIndex() == 1) videoPlayer_->OpenFileName("dinopb.avi");
//    else if( mainTab_->GetIndex() == 2) videoPlayer_->Close();

}

void HomeScreen::HandleGamelistChanged(StringHash eventType, VariantMap& eventData)
{
    
    auto* cache = context_->GetSubsystem<ResourceCache>(); 
    auto* jgamelist = cache->GetResource<JSONFile>("videolist0.json");
    auto  gamelist = jgamelist->GetRoot().GetArray();
    auto  index = gamelist_->GetIndex();
    if(index < gamelist.Size())
    {
        auto video = gamelist[index].GetString();
        LOG_INFOS_CPP(" video " , video.CString());
        videoPlayer_->OpenFileName(video);
    }

}

void HomeScreen::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
}


void HomeScreen::SetGamelist()
{

    auto* cache = context_->GetSubsystem<ResourceCache>(); 
    auto* jgamelist = cache->GetResource<JSONFile>("gamelist2.json");
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


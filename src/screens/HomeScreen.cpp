


#include "HomeScreen.hpp"
#include "../widgets/VideoPlayer.hpp"
#include "../components/VideoPlayerComponent.hpp"
#include "../utils/string.hpp"


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

    videoPlayer_ = screen->GetChildStaticCast<VideoPlayer>(String("VideoPlayer"));

    ChanageToState(state_);

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

    int index = mainTab_->GetIndex();
    switch(index)
    {
        case 0: ChanageToState(State::GAMELIST ); break;
        case 1: ChanageToState(State::RECENT   ); break;
        case 2: ChanageToState(State::FAVORITE ); break;
        default: break;
    }

}

void HomeScreen::HandleGamelistChanged(StringHash eventType, VariantMap& eventData)
{

    UpdateVideoPlayer();
    UpdatePagerIndicator();

}

void HomeScreen::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
}


void HomeScreen::SetGamelist()
{
    auto state = state_;
    // clear data
    gamelist_->ClearItems();
    videoList_.Clear();

    auto cb = [&](const Machine::GameItem& gameItem)->void{
                std::string s = SETTINGS->GetVideoPathFormat().CString();
                auto gameVideoPath = ConstructStringWithFormat(s, gameItem.rom_.CString());
                LOG_INFOS_CPP(" gameVideoPath", gameVideoPath);
                videoList_.Push(ToString(gameVideoPath.c_str()));
                {
                    Gamelist::Item item;
                    std::string s = SETTINGS->GetIconPathFormat().CString();
                    item.iconPath_ =  ConstructStringWithFormat(s, gameItem.rom_.CString()).c_str();
                    item.name_ =  gameItem.name_;
                    gamelist_->AddItem(item);
                }
        };

    // add data 
    switch(state)
    {
        case State::GAMELIST:      MACHINE->HandleAllGames(cb);     break;
        case State::RECENT:        MACHINE->HandleRecentGames(cb);  break;
        case State::FAVORITE:      MACHINE->HandleFavoriteGames(cb);break;
        case State::SEARCH_LOCAL:  break;
        case State::SEARCH_STORE:  break;
    }

    // update gamelist
    gamelist_->ResetIndex();
    gamelist_->Update();
}

void HomeScreen::ChanageToState(State newState)
{
    // leave old state
    State oldState = state_;
    switch(oldState)
    {
        case State::GAMELIST:      break;
        case State::RECENT:        break;
        case State::FAVORITE:      break;
        case State::SEARCH_LOCAL:  break;
        case State::SEARCH_STORE:  break;
    }

    // enter old state
    switch(newState)
    {
        case State::GAMELIST:      break;
        case State::RECENT:        break;
        case State::FAVORITE:      break;
        case State::SEARCH_LOCAL:  break;
        case State::SEARCH_STORE:  break;
    }

    state_ = newState;
    SetGamelist();

    UpdateVideoPlayer();
    UpdatePagerIndicator();

}

void HomeScreen::UpdateVideoPlayer()
{
    auto  index = gamelist_->GetIndex();
    if(index < videoList_.Size())
    {
        auto path = videoList_[index];
        LOG_INFOS_CPP(" video " , path.CString());
        videoPlayer_->OpenFileName(path);
    }

}

void HomeScreen::UpdatePagerIndicator()
{
    auto index = gamelist_->GetIndex();
    auto pageItems = gamelist_->GetPageItems();
    auto gameItemsCount = gamelist_->GetGameItemsCount();
    int c = int((index/pageItems))+1;
    int t = int(((gameItemsCount+pageItems-1)/pageItems));
    pageIndicator_->SetPage(c,t);

}




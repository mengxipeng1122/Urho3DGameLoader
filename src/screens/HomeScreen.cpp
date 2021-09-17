


#include "HomeScreen.hpp"
#include "SettingsScreen.hpp"
#include "../widgets/VideoPlayer.hpp"
#include "../components/VideoPlayerComponent.hpp"
#include "../utils/string.hpp"


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

    mainTab_ = static_cast<MenuBar*>(screen->GetChild(String("Main Tab")));
    ASSERT_CPP(mainTab_!=nullptr, " can not found Main Tab");
    SubscribeToEvent(mainTab_, E_ITEMCHANGED,       URHO3D_HANDLER(HomeScreen, HandleMainTabChanged));
    SubscribeToEvent(mainTab_, E_LOSTSELECTED,      URHO3D_HANDLER(HomeScreen, HandleMainTabLostSelected));
    mainTab_->SetSelected(true);
    SelectWidget(mainTab_);

    searchEdit_ = screen->GetChildStaticCast<SearchEdit>(String("Search Edit"));
    ASSERT_CPP(searchEdit_!=nullptr, " can not found Search Edit");
    searchEdit_ ->SetSelected(false);
    searchEdit_ ->SetVisible(false);

    searchTab_ = static_cast<MenuBar*>(screen->GetChild(String("Search Tab")));
    ASSERT_CPP(searchTab_!=nullptr, " can not found Search Tab");
    SubscribeToEvent(searchTab_, E_ITEMCHANGED,         URHO3D_HANDLER(HomeScreen, HandleSearchTabChanged));
    SubscribeToEvent(searchTab_, E_LOSTSELECTED,        URHO3D_HANDLER(HomeScreen, HandleSearchTabLostSelected));
    searchTab_->SetSelected(false);

    gamelist_ = screen->GetChildStaticCast<Gamelist>(String("Gamelist"));
    ASSERT_CPP(gamelist_!=nullptr, " can not found Gamelist");
    SubscribeToEvent(gamelist_, E_ITEMCHANGED,  URHO3D_HANDLER(HomeScreen, HandleGamelistChanged));
    SubscribeToEvent(gamelist_, E_LOSTSELECTED, URHO3D_HANDLER(HomeScreen, HandleGamelistLostSelected));

    videoPlayer_ = screen->GetChildStaticCast<VideoPlayer>(String("VideoPlayer"));
    ASSERT_CPP(videoPlayer_!=nullptr, " can not found VideoPlayer");

    keyboard_ = screen->GetChildStaticCast<Keyboard>(String("Keyboard"));
    ASSERT_CPP(keyboard_!=nullptr, " can not found keyboard_");
    SubscribeToEvent(keyboard_, E_STRINGCHANGED,     URHO3D_HANDLER(HomeScreen, HandleKeyboardStringChanged));
    SubscribeToEvent(keyboard_, E_LOSTSELECTED,      URHO3D_HANDLER(HomeScreen, HandleKeyboardLostSelected));
    keyboard_->SetSelected(false);
    keyboard_->SetVisible(false);

    ChanageToState(state_);

}

void HomeScreen::Leave()
{
    selectedWidget_ ={nullptr};        
    UnsubscribeFromEvent(mainTab_,      E_ITEMCHANGED);
    UnsubscribeFromEvent(mainTab_,      E_LOSTSELECTED);
    UnsubscribeFromEvent(searchTab_,    E_ITEMCHANGED);
    UnsubscribeFromEvent(searchTab_,    E_LOSTSELECTED);
    UnsubscribeFromEvent(gamelist_,     E_ITEMCHANGED);
    UnsubscribeFromEvent(gamelist_,     E_LOSTSELECTED);
    UnsubscribeFromEvent(this,          E_UPDATE);
    Screen::Leave();
}

bool HomeScreen::HandleKeyDown( InputKey key, int idx)
{
    //using namespace KeyDown;
    if(key == InputKey::SETTING){
        ScreenManager::SetCurrentScreen(SettingsScreen::GetName(), context_);
        return true;
    }

    ASSERT_CPP(mainTab_!=nullptr,   " can not found Main Tab");
    ASSERT_CPP(searchTab_!=nullptr, " can not found search Tab");
    ASSERT_CPP(gamelist_!=nullptr,  " can not found Main Tab");

    if(selectedWidget_!=nullptr)
    {
        bool success = selectedWidget_->HandleKeyDown(key, idx);
        if(success) return true;
    }

    return false;
}

void HomeScreen::HandleMainTabChanged(StringHash eventType, VariantMap& eventData)
{

    int index = mainTab_->GetIndex();
    switch(index)
    {
        case 0: ChanageToState(State::GAMELIST      ); break;
        case 1: ChanageToState(State::RECENT        ); break;
        case 2: ChanageToState(State::FAVORITE      ); break;
        case 3: ChanageToState(State::SEARCH_LOCAL  ); break;
        default: break;
    }
}

void HomeScreen::HandleMainTabLostSelected(StringHash eventType, VariantMap& eventData)
{

    int index = mainTab_->GetIndex();
    switch(index)
    {
        case 0: 
        case 1: 
        case 2:
        {
            auto gameItemsCount = gamelist_->GetGameItemsCount();
            if(gameItemsCount>0) { 
                SelectWidget(gamelist_);
            }
            else { 
                SelectWidget(mainTab_);
            }
        }
        break;

        case 3: 
            SelectWidget(searchTab_.Get());
        break;
        default: ASSERT_CPP("error", index); break;
    }
}


void HomeScreen::HandleSearchTabChanged(StringHash eventType, VariantMap& eventData)
{

    int index = searchTab_->GetIndex();
    switch(index)
    {
        case 0: break;
        case 1: break;
        default: ASSERT_CPP("error", index); break;
    }
}

void HomeScreen::HandleSearchTabLostSelected(StringHash eventType, VariantMap& eventData)
{
    using namespace LostSelected;

    auto key = (InputKey)eventData[P_KEY].GetInt();
    if(key ==  InputKey::UP)
    {
        SelectWidget(mainTab_);
    }
    else if(key ==  InputKey::DOWN)
    {
        SelectWidget(keyboard_); 
        keyboard_->ClearString();
    }
}

void HomeScreen::HandleGamelistChanged(StringHash eventType, VariantMap& eventData)
{

    UpdateVideoPlayer();
    UpdatePagerIndicator();

}

void HomeScreen::HandleGamelistLostSelected(StringHash eventType, VariantMap& eventData)
{
    SelectWidget(mainTab_); 
}

void HomeScreen::HandleKeyboardLostSelected(StringHash eventType, VariantMap& eventData)
{
    SelectWidget(searchTab_); 
}

void HomeScreen::HandleKeyboardStringChanged(StringHash eventType, VariantMap& eventData)
{
    using namespace StringChanged;
    const String s = eventData[P_STRING].GetString();
    searchEdit_->SetTexts(s, 0);

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
}

void HomeScreen::ChanageToState(State newState)
{
    // leave old state
    State oldState = state_;
    switch(oldState)
    {
        case State::GAMELIST:      
        break;

        case State::RECENT:        
        break;

        case State::FAVORITE:      
        break;

        case State::SEARCH_LOCAL:  
        break;

        case State::SEARCH_STORE:  
        break;
    }

    // enter old state
    switch(newState)
    {
        case State::GAMELIST:      
        case State::RECENT:        
        case State::FAVORITE:      
            searchTab_  ->SetVisible(false);
            videoPlayer_->SetVisible(true);
            keyboard_   ->SetVisible(false);
            searchEdit_ ->SetVisible(false);
        break;

        case State::SEARCH_LOCAL:  
        case State::SEARCH_STORE:  
            searchTab_  ->SetVisible(true);
            videoPlayer_->SetVisible(false);
            keyboard_   ->SetVisible(true);
            searchEdit_ ->SetVisible(true);
        break;
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




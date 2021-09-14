
#pragma once

#include "../Global.h"

#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "../widgets/Gamelist.hpp"
#include "../widgets/PageIndicator.hpp"
#include "../widgets/TabSelector.hpp"
#include "../widgets/VideoPlayer.hpp"
class HomeScreen : public Screen
{
    private:
        WeakPtr<PageIndicator> pageIndicator_{nullptr};        
        WeakPtr<TabSelector>   mainTab_{nullptr};        
        WeakPtr<Gamelist>      gamelist_{nullptr};        
        WeakPtr<VideoPlayer>   videoPlayer_{nullptr};        

        Vector<String>         videoList_; // have same id with game list data
        
        void HandleTabChanged(StringHash eventType, VariantMap& eventData);
        void HandleGamelistChanged(StringHash eventType, VariantMap& eventData);
        void HandleUpdate(StringHash eventType, VariantMap& eventData);

        void SetGamelist();

        enum class State
        {
            GAMELIST,
            RECENT,
            FAVORITE,
            SEARCH_LOCAL,
            SEARCH_STORE,
        };

        State state_{State::GAMELIST};

        void ChanageToState(State newState);

        void UpdateVideoPlayer();
        void UpdatePagerIndicator();
    public:
        HomeScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key) override;
        static const char* GetName() {return "Home";}
};


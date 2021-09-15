
#pragma once

#include "../Global.h"

#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "../widgets/Widget.hpp"
#include "../widgets/Keyboard.hpp"
#include "../widgets/Gamelist.hpp"
#include "../widgets/PageIndicator.hpp"
#include "../widgets/TabSelector.hpp"
#include "../widgets/VideoPlayer.hpp"
#include "../widgets/SearchEdit.hpp"

class HomeScreen : public Screen
{
    private:
        WeakPtr<PageIndicator> pageIndicator_{nullptr};        
        WeakPtr<Keyboard>      keyboard_{nullptr};        
        WeakPtr<TabSelector>   mainTab_{nullptr};        
        WeakPtr<TabSelector>   searchTab_{nullptr};        
        WeakPtr<Gamelist>      gamelist_{nullptr};        
        WeakPtr<VideoPlayer>   videoPlayer_{nullptr};        
        WeakPtr<SearchEdit>    searchEdit_{nullptr};        
        Widget*                selectedWidget_{nullptr};        

        Vector<String>         videoList_; // have same id with game list data
        
        void HandleMainTabChanged(StringHash eventType, VariantMap& eventData);
        void HandleMainTabLostSelected(StringHash eventType, VariantMap& eventData);
        void HandleSearchTabChanged(StringHash eventType, VariantMap& eventData);
        void HandleSearchTabLostSelected(StringHash eventType, VariantMap& eventData);
        void HandleGamelistChanged(StringHash eventType, VariantMap& eventData);
        void HandleGamelistLostSelected(StringHash eventType, VariantMap& eventData);
        void HandleUpdate(StringHash eventType, VariantMap& eventData);
        void HandleKeyboardLostSelected(StringHash eventType, VariantMap& eventData);
        void HandleKeyboardStringChanged(StringHash eventType, VariantMap& eventData);

        void SelectWidget(Widget* p) {ASSERT_CPP(p!=nullptr, "can not select nullptr "); selectedWidget_ = p; p->SetSelected(true);}
        
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
        void SetGamelist();

    public:
        HomeScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key, int idx) override;
        static const char* GetName() {return "Home";}
};



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
        
        void HandleTabChanged(StringHash eventType, VariantMap& eventData);
        void HandleGamelistChanged(StringHash eventType, VariantMap& eventData);
        void HandleUpdate(StringHash eventType, VariantMap& eventData);

        void SetGamelist();

    public:
        HomeScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key) override;
        static const char* GetName() {return "Home";}
};


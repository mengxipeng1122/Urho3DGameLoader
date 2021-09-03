
#pragma once

#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "../widgets/Gamelist.hpp"
#include "../widgets/PageIndicator.hpp"
#include "../widgets/TabSelector.hpp"
class HomeScreen : public Screen
{
    private:
        WeakPtr<PageIndicator> pageIndicator_{nullptr};        
        WeakPtr<TabSelector>   mainTab_{nullptr};        
        WeakPtr<Gamelist>      gamelist_{nullptr};        
        
        void HandleTabChanged(StringHash eventType, VariantMap& eventData);

        void SetGamelist();

    public:
        HomeScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(StringHash eventType, VariantMap& eventData) override;
        static const char* GetName() {return "Home";}
};


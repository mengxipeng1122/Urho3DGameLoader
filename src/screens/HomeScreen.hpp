
#pragma once

#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "../widgets/PageIndicator.hpp"
#include "../widgets/TabSelector.hpp"
class HomeScreen : public Screen
{
    private:
        WeakPtr<PageIndicator> pageIndicator_{nullptr};        
        WeakPtr<TabSelector>   mainTab_{nullptr};        
    public:
        void Enter( Context* context) override;
        void Leave( Context* context) override;
        bool HandleKeyDown(Context* context, StringHash eventType, VariantMap& eventData) override;
        static const char* GetName() {return "Home";}
};


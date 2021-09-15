
#pragma once

#include "../Global.h"
#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"


class SettingsScreen : public Screen
{
    private:
        //WeakPtr<PageIndicator> pageIndicator_{nullptr};        

        //void HandleMainTabChanged(StringHash eventType, VariantMap& eventData);


    public:
        SettingsScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key, int idx) override;
        static const char* GetName() {return "Settings";}
};

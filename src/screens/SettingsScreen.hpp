
#pragma once

#include "../Global.h"
#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "../widgets/NormalMenuItem.hpp"


class SettingsScreen : public Screen
{
    private:
        Vector<WeakPtr<Widget>>    menuitems_;
        int                        menuIndex_;

    public:
        SettingsScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key, int idx) override;
        static const char* GetName() {return "Settings";}
};

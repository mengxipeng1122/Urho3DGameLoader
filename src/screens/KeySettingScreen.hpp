
#pragma once

#include "../Global.h"
#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "../widgets/JoystickDir.hpp"
#include "../widgets/JoystickKey.hpp"


class KeySettingScreen : public Screen
{
    public:
        KeySettingScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key, int idx) override;
        bool HandleKeyUp(InputKey key, int idx) override;
        static const char* GetName() {return "KeySetting";}

    private:
};

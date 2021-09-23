
#pragma once

#include "../Global.h"
#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "../widgets/JoystickDir.hpp"
#include "../widgets/JoystickKey.hpp"


class GameSettingScreen : public Screen
{
    public:
        GameSettingScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key, int idx) override;
        bool HandleKeyUp(InputKey key, int idx) override;
        static const char* GetName() {return "GameSetting";}

    private:
};

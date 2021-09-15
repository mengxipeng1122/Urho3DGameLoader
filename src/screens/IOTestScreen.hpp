

#pragma once

#include "../Global.h"

#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"

class IOTestScreen : public Screen
{
    public:
        IOTestScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key, int idx) override;
        static const char* GetName() {return "IOTest";}
};


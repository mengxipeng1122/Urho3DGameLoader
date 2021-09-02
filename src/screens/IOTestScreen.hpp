

#pragma once

#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"

class IOTestScreen : public Screen
{
    public:
        IOTestScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(StringHash eventType, VariantMap& eventData) override;
        static const char* GetName() {return "IOTest";}
};


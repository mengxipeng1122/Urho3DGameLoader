

#pragma once

#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"

class IOTestScreen : public Screen
{
    public:
        void Enter( Context* context) override;
        void Leave( Context* context) override;
        bool HandleKeyDown(Context* context, StringHash eventType, VariantMap& eventData) override;
        static const char* GetName() {return "IOTest";}
};


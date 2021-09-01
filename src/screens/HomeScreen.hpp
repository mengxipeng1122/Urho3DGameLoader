
#pragma once

#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
class HomeScreen : public Screen
{
    public:
        void Enter( Context* context) override;
        void Leave( Context* context) override;
        static const char* GetName() {return "Home";}
};

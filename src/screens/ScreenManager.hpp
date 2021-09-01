
#pragma once

#include <string>
#include <memory>

#include "Screen.hpp"
#include "ScreenBuilder.hpp"
#include "../DP/Factory.hpp"

class ScreenManager
{
    public:
        using ScreenTypes = std::string;
    protected:
        static DP::Factory<ScreenTypes, ScreenBuilder, Screen> s_screenFactory; 
        std::unique_ptr<Screen> currentScreen_{nullptr};
    public:
        ScreenManager();
        virtual ~ScreenManager()=default;

        static void RegistScreen(ScreenTypes& name, ScreenBuilder* builder) { s_screenFactory.AddBuilder(name, builder); }

        void setCurrentScreen(ScreenTypes&);
};



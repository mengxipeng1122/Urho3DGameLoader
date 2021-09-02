
#pragma once

#include <string>
#include <memory>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Core/Context.h>

#include "Screen.hpp"
#include "ScreenBuilder.hpp"
#include "../DP/Factory.hpp"

using namespace Urho3D;

class ScreenManager
{
    public:
        using ScreenTypes = std::string;
    protected:
        static DP::Factory<ScreenTypes, ScreenBuilder, Screen, Context*> s_screenFactory; 
        static std::unique_ptr<Screen> s_currentScreen;
    public:
        ScreenManager();
        virtual ~ScreenManager()=default;

        static void RegistScreen(ScreenTypes& name, ScreenBuilder* builder) { s_screenFactory.AddBuilder(name, builder); }

        static void setCurrentScreen(ScreenTypes, Context* context);
        static void setCurrentScreen(std::unique_ptr<Screen> ptr);

        static bool HandleKeyDown(StringHash eventType, VariantMap& eventData) {return s_currentScreen->HandleKeyDown(eventType, eventData);};
};



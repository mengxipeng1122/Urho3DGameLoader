
#pragma once

#include <vector>
#include <string>
#include <Urho3D/Core/Context.h>
#include "ScreenManager.hpp"

using namespace Urho3D;

class Screen
{
    public:
        Screen()=default;
        virtual ~Screen()=default;
        virtual void Enter( Context* context) = 0;
        virtual void Leave( Context* context) = 0;
};


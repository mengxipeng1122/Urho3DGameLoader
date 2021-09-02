
#pragma once

#include <vector>
#include <string>
#include <Urho3D/Core/Context.h>

using namespace Urho3D;

class Screen
{
    public:
        Screen()=default;
        virtual ~Screen()=default;
        virtual void Enter( Context* context) ;
        virtual void Leave( Context* context) ;
        virtual bool HandleKeyDown(Context* context, StringHash eventType, VariantMap& eventData)=0;
};


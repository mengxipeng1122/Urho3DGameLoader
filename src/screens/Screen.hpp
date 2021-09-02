
#pragma once

#include <vector>
#include <string>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/UI/UIElement.h>

using namespace Urho3D;

class Screen : public UIElement
{
    protected:
    public:
        Screen(Context* context):UIElement(context){}
        virtual ~Screen()=default;
        virtual void Enter() ;
        virtual void Leave() ;
        virtual bool HandleKeyDown(StringHash eventType, VariantMap& eventData)=0;
};


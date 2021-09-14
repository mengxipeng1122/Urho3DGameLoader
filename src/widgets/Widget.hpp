#pragma once

#include "../Global.h"
 
namespace Urho3D
{

class Widget : public UIElement
{
    public:
        Widget(Context* context) : UIElement(context) {}
        virtual bool HandleKeyDown(InputKey key)=0;
};

}


#pragma once

#include <vector>
#include <string>
#include "../Global.h"
#include "../InputSystem.hpp"


class Screen : public UIElement
{
    protected:
    public:
        Screen(Context* context):UIElement(context){}
        virtual ~Screen()=default;
        virtual void Enter() ;
        virtual void Leave() ;
        virtual bool HandleKeyDown(InputKey key)=0;
};


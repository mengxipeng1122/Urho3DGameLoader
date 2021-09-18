

#pragma once
#include "Widget.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{



//=============================================================================
//=============================================================================
class MenuItem : public Widget
{
    URHO3D_OBJECT(MenuItem, Widget);
public:
    static void RegisterObject(Context* context);

    explicit MenuItem(Context *context) :Widget(context){ }


public:
    void Update();


protected:

private:


};

}



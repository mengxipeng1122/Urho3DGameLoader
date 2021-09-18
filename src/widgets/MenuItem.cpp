

#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "MenuItem.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
//=============================================================================
void MenuItem::RegisterObject(Context* context)
{
    context->RegisterFactory<MenuItem>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Widget);

}

MenuItem::MenuItem(Context *context)
    : Widget(context)
{
}



}




#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "Widget.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
//=============================================================================
void Widget::RegisterObject(Context* context)
{
    context->RegisterFactory<Widget>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);

}

Widget::Widget(Context *context)
    : UIElement(context)
{
}



}

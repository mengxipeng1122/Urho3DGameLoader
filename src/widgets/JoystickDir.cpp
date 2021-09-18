#include "JoystickDir.hpp"
#include "../utils/log.hpp"
#include "../utils/string.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
void JoystickDir::RegisterObject(Context* context)
{
    context->RegisterFactory<JoystickDir>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Widget);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Images", GetImagesAttr, SetImagesAttr, VariantVector, Variant::emptyVariantVector, AM_FILE);
}

JoystickDir::JoystickDir(Context *context)
    : Widget(context)
{
}


void JoystickDir::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    auto texture = CACHE->GetResource<Texture2D>(images_[static_cast<int>(state_)]);
    Widget::AddTextureBatch(batches, vertexData, currentScissor, texture, 0, 0);
}


}

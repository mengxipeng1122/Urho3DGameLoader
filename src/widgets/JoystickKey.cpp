#include "JoystickKey.hpp"
#include "../utils/log.hpp"
#include "../utils/string.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
void JoystickKey::RegisterObject(Context* context)
{
    context->RegisterFactory<JoystickKey>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Widget);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Image", GetImageTextureAttr, SetImageTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Image Scale", float, imageScale_, 1.2, AM_FILE);
}

JoystickKey::JoystickKey(Context *context)
    : Widget(context)
{
}


void JoystickKey::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    auto texture = CACHE->GetResource<Texture2D>(imageTexture_);
    auto w = texture->GetWidth();
    auto h = texture->GetHeight();
    if(state_)
    {
        w*=imageScale_;
        h*=imageScale_;
    }
    Widget::AddTextureBatch(batches, vertexData, currentScissor, texture, 0, 0, w,h);
}


}

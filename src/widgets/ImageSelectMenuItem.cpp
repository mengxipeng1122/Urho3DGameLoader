
#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "ImageSelectMenuItem.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
//=============================================================================
void ImageSelectMenuItem::RegisterObject(Context* context)
{
    context->RegisterFactory<ImageSelectMenuItem>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(SelectMenuItem);
}

ImageSelectMenuItem::ImageSelectMenuItem(Context *context)
    : SelectMenuItem(context)
{
}

void ImageSelectMenuItem::GetBatchesForOption(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    {
        auto font = CACHE->GetResource<Font>(textFont_);
        FontFace* face = font->GetFace(textFontSize_);
        ASSERT_CPP(optionsIndex_>=0 && optionsIndex_<options_.Size(), "optionsIndex_ error", optionsIndex_, "/", options_.Size());
        auto* texture = CACHE->GetResource<Texture2D>(options_[optionsIndex_]);
        auto offsetx = optionPosition_.x_ - texture->GetWidth()/2;
        auto offsety = optionPosition_.y_;
        Widget::AddTextureBatch(
                batches
              , vertexData
              , currentScissor
              , texture
              , offsetx
              , offsety
              );
    }
}



}

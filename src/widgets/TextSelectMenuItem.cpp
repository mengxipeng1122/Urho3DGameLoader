
#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "TextSelectMenuItem.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
//=============================================================================
void TextSelectMenuItem::RegisterObject(Context* context)
{
    context->RegisterFactory<TextSelectMenuItem>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(NormalMenuItem);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Unselect Left Arrow Texture", GetUnselectLeftArrowTextureAttr, SetUnselectLeftArrowTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Select Left Arrow Texture", GetSelectLeftArrowTextureAttr, SetSelectLeftArrowTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Left Arrow Position", Vector2, leftArrowPosition_, Vector2::ZERO, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Unselect Right Arrow Texture", GetUnselectRightArrowTextureAttr, SetUnselectRightArrowTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Select Right Arrow Texture", GetSelectRightArrowTextureAttr, SetSelectRightArrowTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Right Arrow Position", Vector2, rightArrowPosition_, Vector2::ZERO, AM_FILE);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Options", GetOptionsAttr, SetOptionsAttr, VariantVector, Variant::emptyVariantVector, AM_FILE);
    URHO3D_ATTRIBUTE("Option Position", Vector2, optionPosition_, Vector2::ZERO, AM_FILE);

}

TextSelectMenuItem::TextSelectMenuItem(Context *context)
    : NormalMenuItem(context)
{
}

void TextSelectMenuItem::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    NormalMenuItem::GetBatches(batches, vertexData, currentScissor);

    // draw left arrow
    {
        Widget::AddTextureBatch(
              batches
            , vertexData
            , currentScissor
            , IsSelected() ? CACHE->GetResource<Texture2D>(selectLeftArrowTexture_) 
                           : CACHE->GetResource<Texture2D>(unselectLeftArrowTexture_)
            , leftArrowPosition_.x_ 
            , leftArrowPosition_.y_ 
            );
    }
    // draw right arrow
    {
        Widget::AddTextureBatch(
              batches
            , vertexData
            , currentScissor
            , IsSelected() ? CACHE->GetResource<Texture2D>(selectRightArrowTexture_) 
                           : CACHE->GetResource<Texture2D>(unselectRightArrowTexture_)
            , rightArrowPosition_.x_ 
            , rightArrowPosition_.y_ 
            );
    }
    // draw options
    {
        auto font = CACHE->GetResource<Font>(textFont_);
        FontFace* face = font->GetFace(textFontSize_);
        ASSERT_CPP(optionsIndex_>=0 && optionsIndex_<options_.Size(), "optionsIndex_ error", optionsIndex_, "/", options_.Size());
        const String& str = options_[optionsIndex_];
        const int stringLineLength = Widget::GetStringLineWidth(str, face);
        auto offsetx = optionPosition_.x_ - stringLineLength/2;
        auto offsety = optionPosition_.y_;
        Widget::AddStringBatch(
              batches
              , vertexData
              , currentScissor
              , str
              , face
              , IsSelected() ? selectColor_ : unselectColor_
              , offsetx
              , offsety
              );
    }
}

bool TextSelectMenuItem::HandleKeyDown(InputKey key, int idx)
{
    bool handled = NormalMenuItem::HandleKeyDown(key, idx); 
    if(handled) return true;

    switch(key)
    {
        case InputKey::LEFT : { 
            if (optionsIndex_>0) {
                optionsIndex_ --;
            }
            else {
                optionsIndex_ = options_.Size()-1;
            }
            return  true;
        }

        case InputKey::RIGHT:{ 
            optionsIndex_++;
            optionsIndex_ %= options_.Size();
            return  true;
        }
    }
    return false;
}


}

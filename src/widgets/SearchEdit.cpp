
#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "SearchEdit.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
//=============================================================================
void SearchEdit::RegisterObject(Context* context)
{
    context->RegisterFactory<SearchEdit>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Widget);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Background Texture", GetBackgroundTextureAttr, SetBackgroundTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);

    URHO3D_ATTRIBUTE("Text Color", Color, textColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Text Font", GetTextFontAttr, SetTextFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Text Font Size", float, textFontSize_, DEFAULT_FONT_SIZE, AM_FILE);

    URHO3D_ATTRIBUTE("Key Base Position", Vector2, keyBasePosition_, Vector2::ZERO, AM_FILE);
    URHO3D_ATTRIBUTE("Count Base Position", Vector2, countBasePosition_, Vector2::ZERO, AM_FILE);

    URHO3D_ATTRIBUTE("Key Text Gap", int, keyStringGap_, 15, AM_FILE);
}

SearchEdit::SearchEdit(Context *context)
    : Widget(context)
{
}

void SearchEdit::ApplyAttributes()
{
    Widget::ApplyAttributes();
    Update();
    return;
}

void SearchEdit::Update()
{
}

void SearchEdit::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    {
        auto texture = CACHE->GetResource<Texture2D>(backgroundTexture_);
        Widget::AddTextureBatch(batches, vertexData, currentScissor, texture, 0, 0);
    }
    {
        auto font = CACHE->GetResource<Font>(textFont_);
        FontFace* face = font->GetFace(textFontSize_);
        auto str  = key_;
        int dx=keyBasePosition_.x_;
        int dy=keyBasePosition_.y_;
        Widget::AddStringBatch(batches, vertexData, currentScissor, str, face, textColor_, dx, dy, keyStringGap_);
    }
    {
        auto font = CACHE->GetResource<Font>(textFont_);
        FontFace* face = font->GetFace(textFontSize_);
        auto str  = String(count_);
        int dx=countBasePosition_.x_;
        int dy=countBasePosition_.y_;
        Widget::AddStringBatch(batches, vertexData, currentScissor, str, face, textColor_, dx, dy);
    }
}



}

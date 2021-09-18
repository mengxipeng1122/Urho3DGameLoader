
#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "NormalMenuItem.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
//=============================================================================
void NormalMenuItem::RegisterObject(Context* context)
{
    context->RegisterFactory<NormalMenuItem>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Widget);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Unselect Background Texture", GetUnselectBackgroundTextureAttr, SetUnselectBackgroundTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Select Background Texture", GetSelectBackgroundTextureAttr, SetSelectBackgroundTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Select Color", Color, selectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_ATTRIBUTE("Unselect Color", Color, unselectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_ATTRIBUTE("Text", String, text_, String::EMPTY, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Text Font", GetTextFontAttr, SetTextFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Text Font Size", float, textFontSize_, DEFAULT_FONT_SIZE, AM_FILE);
    URHO3D_ATTRIBUTE("Text Auto Localizable", bool, textAutoLocalizable_, false, AM_FILE);
    URHO3D_ATTRIBUTE("Text Base Position", Vector2, textBasePosition_, Vector2::ZERO, AM_FILE);

}

NormalMenuItem::NormalMenuItem(Context *context)
    : MenuItem(context)
{
}

void NormalMenuItem::ApplyAttributes()
{
    Widget::ApplyAttributes();
    return;
}


void NormalMenuItem::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    auto unselectBackgroundTexture = CACHE->GetResource<Texture2D>(unselectBackgroundTexture_);
    // draw background
    {
        if(IsSelected()) {
            auto selectBackgroundTexture = CACHE->GetResource<Texture2D>(selectBackgroundTexture_);
            Widget::AddTextureBatch(batches, vertexData, currentScissor, selectBackgroundTexture, 0,0);
        }
        else {
            Widget::AddTextureBatch(batches, vertexData, currentScissor, unselectBackgroundTexture, 0,0);
        }
    }
    // draw text
    {
        auto font = CACHE->GetResource<Font>(textFont_);
        FontFace* face = font->GetFace(textFontSize_);
        const IntVector2 cursorSize{unselectBackgroundTexture->GetWidth(), unselectBackgroundTexture->GetHeight()};
        const auto& position = GetPosition();
        auto offsety = textBasePosition_.x_;
        auto offsetx = textBasePosition_.y_;
        String str;
        if(textAutoLocalizable_) {
            str = L10N->Get(text_);
        }
        else{
            str = text_;
        }
        Widget::AddStringBatch(batches, vertexData, currentScissor, str, face, IsSelected() ? selectColor_ : unselectColor_, offsetx, offsety);
    }
}

bool NormalMenuItem::HandleKeyDown(InputKey key, int idx)
{
    return false;
}


}

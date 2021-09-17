#include "MenuBar.hpp"
#include "../utils/log.hpp"
#include "../utils/string.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
void MenuBar::RegisterObject(Context* context)
{
    context->RegisterFactory<MenuBar>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Widget);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Background Texture", GetBackgroundTextureAttr, SetBackgroundTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Texts", GetTextsAttr, SetTextsAttr, VariantVector, Variant::emptyVariantVector, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Select Cursor Texture", GetSelectCursorTextureAttr, SetSelectCursorTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Unselect Cursor Texture", GetUnselectCursorTextureAttr, SetUnselectCursorTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Select Color", Color, selectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_ATTRIBUTE("UnSelect Color", Color, unselectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Text Font", GetTextFontAttr, SetTextFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Text Font Size", float, textFontSize_, DEFAULT_FONT_SIZE, AM_FILE);
    URHO3D_ATTRIBUTE("Text Auto Localization", bool, textAutoLocalization_, false, AM_FILE);
    URHO3D_ATTRIBUTE("Cursor Base Position", Vector2, cursorBasePosition_, Vector2::ZERO, AM_FILE);
    URHO3D_ATTRIBUTE("Auto Localizable", bool, autoLocalizable_, false, AM_FILE);
}

MenuBar::MenuBar(Context *context)
    : Widget(context)
{
}


bool MenuBar::HandleKeyDown(InputKey key, int idx)
{
    if(!IsSelected()) return false;

    if(     key == InputKey::UP
        ||  key == InputKey::DOWN
        )
    {
        SetSelected(false);
        Widget::SendLostSelectedEvent(key, idx);
        return true;
    }

    bool indexChanged = false;
    bool handledKey = false;
    if(key == InputKey::LEFT) 
    {
        if(index_>0)
        {
            indexChanged = true;
            index_--; 
        }
        handledKey = true;
    }
    else if(key == InputKey::RIGHT)
    {
        if(index_<texts_.Size()-1) 
        {
            indexChanged = true;
            index_++;
        }
        handledKey = true;
    }

    if(indexChanged)
    {
        Widget::SendItemChangedEvent(index_);
    }

    return (handledKey);
}

void MenuBar::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    // draw background
    {
        auto texture = CACHE->GetResource<Texture2D>(backgroundTexture_);
        Widget::AddTextureBatch(batches, vertexData, currentScissor, texture, 0, 0);
    }

    // draw cursor
    {
        if(IsSelected()) {
            auto texture = CACHE->GetResource<Texture2D>(selectCursorTexture_);
            const IntVector2 cursorSize{texture->GetWidth(), texture->GetHeight()};
            Widget::AddTextureBatch(batches, vertexData, currentScissor, texture, cursorBasePosition_.x_+index_*cursorSize.x_, cursorBasePosition_.y_);
        }
        else {
            auto texture = CACHE->GetResource<Texture2D>(unselectCursorTexture_);
            const IntVector2 cursorSize{texture->GetWidth(), texture->GetHeight()};
            Widget::AddTextureBatch(batches, vertexData, currentScissor, texture, cursorBasePosition_.x_+index_*cursorSize.x_, cursorBasePosition_.y_);
        }
    }

    // draw texts
    {
        auto font = CACHE->GetResource<Font>(textFont_);
        FontFace* face = font->GetFace(textFontSize_);
        auto selectCursorTexture = CACHE->GetResource<Texture2D>(selectCursorTexture_);
        const IntVector2 cursorSize{selectCursorTexture->GetWidth(), selectCursorTexture->GetHeight()};
        for( int i = 0; i<texts_.Size() ;i++) {
            auto str = texts_[i];
            if(autoLocalizable_) str = L10N->Get(str);

            int dx=cursorBasePosition_.x_+cursorSize.x_*i;
            int dy=cursorBasePosition_.y_;
            if( i == index_) {
                Widget::AddStringBatch(batches, vertexData, currentScissor, str, face, selectColor_, dx, dy, -1, cursorSize.x_, cursorSize.y_);
            }
            else {
                Widget::AddStringBatch(batches, vertexData, currentScissor, str, face, unselectColor_, dx, dy, -1, cursorSize.x_, cursorSize.y_);
            }
        }
    }
}


}

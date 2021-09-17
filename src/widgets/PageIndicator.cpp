
#include "PageIndicator.hpp"
#include "../utils/log.hpp"
#include "../utils/string.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
void PageIndicator::RegisterObject(Context* context)
{
    context->RegisterFactory<PageIndicator>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Widget);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Background Texture", GetBackgroundTextureAttr, SetBackgroundTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Text Font", GetTextFontAttr, SetTextFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Text Font Size", float, textFontSize_, DEFAULT_FONT_SIZE, AM_FILE);
    URHO3D_ATTRIBUTE("Text Color", Color, textColor_, Color::WHITE, AM_FILE);
    URHO3D_ATTRIBUTE("Text Position", Vector2, textPosition_, Vector2::ZERO, AM_FILE);
}

PageIndicator::PageIndicator(Context *context)
    : Widget(context)
{
}

void PageIndicator::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
 //   LOG_INFOS_CPP("gohere");
//    return ;
//    {
//        auto texture = CACHE->GetResource<Texture2D>(backgroundTexture_);
//        Widget::AddTextureBatch(batches, vertexData, currentScissor, texture, 0, 0);
//    }
//    {
//        auto font = CACHE->GetResource<Font>(textFont_);
//        ASSERT_CPP(font!=nullptr, "font is nullptr");
//        FontFace* face = font->GetFace(textFontSize_);
//        int dx=textPosition_.x_;
//        int dy=textPosition_.y_;
//        String s; s.AppendWithFormat("%d/%d",curPageNo_, totalPageNo_);
//        int x = textPosition_.x_;
//        int y = textPosition_.y_;
//        Widget::AddStringBatch(batches, vertexData, currentScissor, s, face, textColor_, x, y);
//    }
}

}

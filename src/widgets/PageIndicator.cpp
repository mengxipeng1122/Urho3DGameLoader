
#include "PageIndicator.hpp"
#include "../utils/log.hpp"
#include "../utils/string.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

#include <Urho3D/DebugNew.h>
//=============================================================================
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


// void PageIndicator::Quit()
// {
//     UnsubscribeFromEvent(E_UPDATE);
// }

// bool PageIndicator::LoadXML(const XMLElement& source, XMLFile* styleFile)
// {
//     bool success = Widget::LoadXML(source, styleFile);
//     ASSERT_CPP(success, "load XML failed ");
//     // get bg
//     bg_   = static_cast<Sprite*>(GetChild(String("bg")));
//     ASSERT_CPP(bg_!=nullptr, " can not found bg ");
//     text_ = static_cast<Text*>(GetChild(String("text")));
//     ASSERT_CPP(text_!=nullptr, " can not found text ");
//     //SetText();
// 
//     return success;
// }
// 
// void PageIndicator::HandleUpdate(StringHash eventType, VariantMap& eventData)
// {
//     using namespace Update;
// 
// }

// void PageIndicator::SetText()
// {
//     ASSERT_CPP(text_!=nullptr, " can not get text");
//     LOG_INFOS_CPP(" go here ");
//     std::string s = ConstructStringWithFormat("%03d/%04d",curPageNo_, totalPageNo_);
//     text_->SetText(ToString(s.c_str()));
// }
// 
// 
// void PageIndicator::Update()
// {
//     bg_=static_cast<Sprite*>(GetChild(String("bg")));
//     ASSERT_CPP(bg_!=nullptr, " can not get bg");
//     text_=static_cast<Text*>(GetChild(String("bg")));
//     ASSERT_CPP(text_!=nullptr, " can not get text");
//     SetText();
// }

void PageIndicator::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    {
        auto texture = CACHE->GetResource<Texture2D>(backgroundTexture_);
        Widget::AddTextureBatch(batches, vertexData, currentScissor, texture, 0, 0);
    }
    {
        auto font = CACHE->GetResource<Font>(textFont_);
        ASSERT_CPP(font!=nullptr, "font is nullptr");
        FontFace* face = font->GetFace(textFontSize_);
        int dx=textPosition_.x_;
        int dy=textPosition_.y_;
        String s; s.AppendWithFormat("%d/%d",curPageNo_, totalPageNo_);
        int x = textPosition_.x_;
        int y = textPosition_.y_;
        Widget::AddStringBatch(batches, vertexData, currentScissor, s, face, textColor_, x, y);
    }
}

}

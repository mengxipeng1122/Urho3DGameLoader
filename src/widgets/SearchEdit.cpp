
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
    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Background Texture", GetBackgroundTextureAttr, SetBackgroundTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);

    URHO3D_ATTRIBUTE("Text Color", Color, textColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Text Font", GetTextFontAttr, SetTextFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Text Font Size", float, textFontSize_, DEFAULT_FONT_SIZE, AM_FILE);

    URHO3D_ATTRIBUTE("Key Base Position", Vector2, keyBasePosition_, Vector2::ZERO, AM_FILE);
    URHO3D_ATTRIBUTE("Count Base Position", Vector2, countBasePosition_, Vector2::ZERO, AM_FILE);
}

SearchEdit::SearchEdit(Context *context)
    : UIElement(context)
{
}

bool SearchEdit::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    bool success = UIElement::LoadXML(source, styleFile);
    ASSERT_CPP(success, "load XML failed ");

    CreateChildren();
    Update();

    return success;
}

void SearchEdit::Update()
{
    GetChildStaticCast<Text>(String("key"))->SetText(key_);
    GetChildStaticCast<Text>(String("count"))->SetText(String(count_));
}

void SearchEdit::CreateChildren()
{
    RemoveAllChildren();
    {
        auto texture = CACHE->GetResource<Texture2D>(backgroundTexture_);
        ASSERT_CPP(texture != nullptr, " load Texture2D of ", backgroundTexture_.CString(), "failed");
        auto bg = CreateChild<Sprite>(String("bg"));
        bg ->SetSize(texture->GetWidth(), texture->GetHeight());
        bg ->SetTexture(texture);
        bg ->SetBlendMode(BLEND_ALPHA);
    }
    {
        auto keyText = CreateChild<Text>(String("key"));
        auto font = CACHE->GetResource<Font>(textFont_);
        keyText->SetTextAlignment(HA_CENTER);
        keyText->SetFont(font, textFontSize_);
        keyText->SetColor(textColor_);
    }
    {
        auto countText = CreateChild<Text>(String("count"));
        auto font = CACHE->GetResource<Font>(textFont_);
        countText->SetTextAlignment(HA_CENTER);
        countText->SetFont(font, textFontSize_);
        countText->SetColor(textColor_);
    }


}


}

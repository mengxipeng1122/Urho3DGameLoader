
#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "KeyBoard.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
//=============================================================================
void KeyBoard::RegisterObject(Context* context)
{
    context->RegisterFactory<KeyBoard>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Key Background Texture", GetKeyBackgroundTextureAttr, SetKeyBackgroundTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Key Select Texture", GetKeySelectTextureAttr, SetKeySelectTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Key Clear Texture", GetKeyClearTextureAttr, SetKeyClearTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Key Del Texture", GetKeyDelTextureAttr, SetKeyDelTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Key Shift Texture", GetKeyShiftTextureAttr, SetKeyShiftTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Key Space Texture", GetKeySpaceTextureAttr, SetKeySpaceTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Text Font", GetTextFontAttr, SetTextFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Text Unselect Color", Color, textUnselectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_ATTRIBUTE("Text Select Color", Color, textSelectColor_, Color::WHITE, AM_FILE);
    URHO3D_ATTRIBUTE("Text Font Size", float, textFontSize_, DEFAULT_FONT_SIZE, AM_FILE);

    URHO3D_ATTRIBUTE("Key Gap", Vector2, keyGap_, Vector2::ZERO, AM_FILE);
}

KeyBoard::KeyBoard(Context *context)
    : Widget(context)
{
}

bool KeyBoard::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    bool success = UIElement::LoadXML(source, styleFile);
    ASSERT_CPP(success, "load XML failed ");

    CreateChildren();
    Update();

    return success;
}

void KeyBoard::Update()
{
//    GetChildStaticCast<Text>(String("key"))->SetText(key_);
}

void KeyBoard::CreateChildren()
{
    RemoveAllChildren();
    auto keyBackgroundTexture = CACHE->GetResource<Texture2D>(keyBackgroundTexture_);
    ASSERT_CPP(keyBackgroundTexture != nullptr, " load Texture2D of ", keyBackgroundTexture_.CString(), "failed");
    auto keySelectTexture = CACHE->GetResource<Texture2D>(keySelectTexture_);
    ASSERT_CPP(keySelectTexture != nullptr, " load Texture2D of ", keySelectTexture_.CString(), "failed");
    constexpr const int cols = 10;
    constexpr const int rows = 4;
    constexpr std::array<char, cols*rows> chars = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '\x0', // clear
        'Z', 'X', 'C', 'V', ' ', 'B', 'N', 'M', '-', '\x8', // backspace
        };
    for(auto r=0;r<rows;r++)
    {
        for(auto c=0;c<cols;c++)
        {
            auto idx = cols*r+c;
            {
                auto& texture = keyBackgroundTexture;
                auto bg = CreateChild<Sprite>(String("bg")+String(idx));
                bg ->SetSize(texture->GetWidth(), texture->GetHeight());
                bg ->SetTexture(texture);
                bg ->SetBlendMode(BLEND_ALPHA);
                auto x=c*(texture->GetWidth() +keyGap_.x_);
                auto y=r*(texture->GetHeight()+keyGap_.y_);
                bg->SetPosition(x,y);
            }
            {
                // auto& texture = keyBackgroundTexture;
                // auto text = CreateChild<Text>(String("bg")+String(idx));
                // text ->SetSize(texture->GetWidth(), texture->GetHeight());
                // text ->SetTexture(texture);
                // text ->SetBlendMode(BLEND_ALPHA);
            }
        }
    }


}

bool KeyBoard::HandleKeyDown(InputKey key)
{
    return false;
}



}

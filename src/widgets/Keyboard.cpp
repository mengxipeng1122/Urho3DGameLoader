
#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "Keyboard.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
//=============================================================================
void Keyboard::RegisterObject(Context* context)
{
    context->RegisterFactory<Keyboard>(UI_CATEGORY);
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

Keyboard::Keyboard(Context *context)
    : Widget(context)
{
}

bool Keyboard::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    bool success = UIElement::LoadXML(source, styleFile);
    ASSERT_CPP(success, "load XML failed ");

    //CreateChildren();
    Update();

    return success;
}

void Keyboard::Update()
{
//    GetChildStaticCast<Text>(String("key"))->SetText(key_);
}

void Keyboard::CreateChildren()
{
    RemoveAllChildren();
    auto keyBackgroundTexture = CACHE->GetResource<Texture2D>(keyBackgroundTexture_);
    ASSERT_CPP(keyBackgroundTexture != nullptr, " load Texture2D of ", keyBackgroundTexture_.CString(), "failed");
    auto keySelectTexture = CACHE->GetResource<Texture2D>(keySelectTexture_);
    ASSERT_CPP(keySelectTexture != nullptr, " load Texture2D of ", keySelectTexture_.CString(), "failed");
    for(auto r=0;r<rows_;r++)
    {
        for(auto c=0;c<cols_;c++)
        {
            auto idx = cols_*r+c;
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
        }
    }
    for(auto r=0;r<rows_;r++)
    {
        for(auto c=0;c<cols_;c++)
        {
            auto idx = cols_*r+c;
            {
                auto& texture = keyBackgroundTexture;
                auto text = CreateChild<Text>(String("text")+String(idx));
                text ->SetSize(texture->GetWidth(), texture->GetHeight());
                text ->SetText(String(chars_[idx]));
                //text ->SetTextAlignment(HA_CENTER);
                auto font = CACHE->GetResource<Font>(textFont_);
                text ->SetFont(font, textFontSize_);
                text ->SetColor(textUnselectColor_);
                auto x=c*(texture->GetWidth() +keyGap_.x_);
                auto y=r*(texture->GetHeight()+keyGap_.y_);
                text ->SetPosition(x,y);
            }
        }
    }
}

bool Keyboard::HandleKeyDown(InputKey key)
{
    {
        auto oldCurrChar = currChar_;
        auto keyGridsCount = cols_*rows_;
        if(currChar_>=0 &&  currChar_< keyGridsCount)
        {
            if(key == InputKey::UP_1P     ){ if(currChar_-cols_>=0)currChar_ -=cols_;                           return true; }
            if(key == InputKey::DOWN_1P   ){ if(currChar_+cols_<keyGridsCount)currChar_ +=cols_;                return true; }
            if(key == InputKey::LEFT_1P   ){ currChar_ --;  currChar_ = std::max(currChar_, 0);                 return true; }
            if(key == InputKey::RIGHT_1P  ){ currChar_ ++;  currChar_ = std::min(keyGridsCount-1, currChar_);   return true; }
        }
        else
        {
            ASSERT_CPP(false, " currChar_ is not correct ", currChar_, "/", keyGridsCount);
        }

    }
    {
        if(key == InputKey::FIRE_A_1P)
        {
            auto l = str_.Length();
            switch(currChar_)
            {
                case 0 : 
                case 1 : 
                case 2 : 
                case 3 : 
                case 4 : 
                case 5 : 
                case 6 : 
                case 7 : 
                case 8 : 
                case 9 : 
                case 10: 
                case 11: 
                case 12: 
                case 13: 
                case 14: 
                case 15: 
                case 16: 
                case 17: 
                case 18: 
                case 19: 
                case 20: 
                case 21: 
                case 22: 
                case 23: 
                case 24: 
                case 25: 
                case 26: 
                case 27: 
                case 28: {if(l<MAX_TEXT_LANGTH-1){ str_+=chars_[currChar_];}} break;
                case 29: {str_.Clear();                        } break; // delete call 
                case 30: 
                case 31: 
                case 32: 
                case 33: 
                case 34: 
                case 35: 
                case 36: 
                case 37: 
                case 38: {if(l<MAX_TEXT_LANGTH-1){ str_+=chars_[currChar_];}} break;
                case 39: {if(l>0){ str_ = str_.Substring(0, l-1);  }} break; // deltete the last character
            }
            {
                LOG_INFOS_CPP(" displayText  ", str_);
            }
            return true;
        }
    }
    return false;
}

void Keyboard::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    auto keyBackgroundTexture = CACHE->GetResource<Texture2D>(keyBackgroundTexture_ );
    auto keySelectTexture     = CACHE->GetResource<Texture2D>(keySelectTexture_     );
    auto keyClearTexture      = CACHE->GetResource<Texture2D>(keyClearTexture_      );
    auto keyDelTexture        = CACHE->GetResource<Texture2D>(keyDelTexture_        );
    auto keySpaceTexture      = CACHE->GetResource<Texture2D>(keySpaceTexture_      );

    auto font = CACHE->GetResource<Font>(textFont_);
    FontFace* face = font->GetFace(textFontSize_);

    auto textureWidth = keyBackgroundTexture->GetWidth();
    auto textureHeight= keyBackgroundTexture->GetHeight();

    // draw bg backgounds
    for(auto r=0;r<rows_;r++)
    {
        for(auto c=0;c<cols_;c++)
        {
            auto idx = cols_*r+c;
            {
                auto x=c*(textureWidth   +keyGap_.x_);
                auto y=r*(textureHeight  +keyGap_.y_);
                Widget::AddTextureBatch(batches, vertexData, currentScissor, keyBackgroundTexture, x, y);
            }
        }
    }

    // draw cursor
    if(IsSelected())
    {
        auto r = currChar_ / cols_;
        auto c = currChar_ % cols_;
        auto x=c*(textureWidth   +keyGap_.x_);
        auto y=r*(textureHeight  +keyGap_.y_);
        Widget::AddTextureBatch(batches, vertexData, currentScissor, keySelectTexture, x, y);
    }

    // draw character
    for(auto r=0;r<rows_;r++)
    {
        for(auto c=0;c<cols_;c++)
        {
            auto idx = cols_*r+c;
            {
                auto x=c*(textureWidth   +keyGap_.x_);
                auto y=r*(textureHeight  +keyGap_.y_);
                auto ch = chars_[idx];
                if(ch == CHAR_CLEAR)
                {
                    Widget::AddTextureBatch(batches, vertexData, currentScissor, keyClearTexture, x, y);
                }
                else if( ch== CHAR_DEL)
                {
                    Widget::AddTextureBatch(batches, vertexData, currentScissor, keyClearTexture, x, y);
                }
                else if( ch== CHAR_SPACE)
                {
                    Widget::AddTextureBatch(batches, vertexData, currentScissor, keySpaceTexture, x, y);
                }
                else
                {
                    Widget::AddCharBatch(batches, vertexData, currentScissor, ch, face, textUnselectColor_, x,y, textureWidth, textureHeight);
                }
            }
        }
    }
    return ;
}


}

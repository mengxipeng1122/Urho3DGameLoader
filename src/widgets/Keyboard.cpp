
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
    URHO3D_COPY_BASE_ATTRIBUTES(Widget);

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

bool Keyboard::HandleKeyDown(InputKey key, int idx)
{
    if(key == InputKey::START)
    {
        SetSelected(false);
        Widget::SendLostSelectedEvent(key, idx); 
        return true;
    }
    {
        auto oldCurrChar = currChar_;
        auto keyGridsCount = cols_*rows_;
        if(currChar_>=0 &&  currChar_< keyGridsCount)
        {
            if(key == InputKey::UP     )
            { 
                if(currChar_-cols_>=0)
                {
                    currChar_ -=cols_; 
                }
                else
                {
                    SetSelected(false);
                    Widget::SendLostSelectedEvent(key, idx);
                }  
                return true; 
            }
            if(key == InputKey::DOWN   ){ if(currChar_+cols_<keyGridsCount)currChar_ +=cols_;                return true; }
            if(key == InputKey::LEFT   ){ currChar_ --;  currChar_ = std::max(currChar_, 0);                 return true; }
            if(key == InputKey::RIGHT  ){ currChar_ ++;  currChar_ = std::min(keyGridsCount-1, currChar_);   return true; }
        }
        else
        {
            ASSERT_CPP(false, " currChar_ is not correct ", currChar_, "/", keyGridsCount);
        }

    }
    {
        if(key == InputKey::FIRE_A)
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
                SendStringChanagedEvent(str_);
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
                    Widget::AddTextureBatch(batches, vertexData, currentScissor, keyDelTexture,   x, y);
                }
                else if( ch== CHAR_SPACE)
                {
                    Widget::AddTextureBatch(batches, vertexData, currentScissor, keySpaceTexture, x, y);
                }
                else
                {
                    if(IsSelected() && idx == currChar_)
                    {
                        Widget::AddCharBatch(batches, vertexData, currentScissor, ch, face, textSelectColor_, x,y, textureWidth, textureHeight);
                    }
                    else
                    {
                        Widget::AddCharBatch(batches, vertexData, currentScissor, ch, face, textUnselectColor_, x,y, textureWidth, textureHeight);
                    }
                }
            }
        }
    }
    return ;
}


}

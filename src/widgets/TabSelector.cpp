#include "TabSelector.hpp"
#include "../utils/log.hpp"
#include "../utils/string.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
void TabSelector::RegisterObject(Context* context)
{
    context->RegisterFactory<TabSelector>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);

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


}

TabSelector::TabSelector(Context *context)
    : Widget(context)
{
    //CreateChildren();
    //Update();
}


void TabSelector::Quit()
{
    UnsubscribeFromEvent(E_UPDATE);
}

bool TabSelector::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    bool success = UIElement::LoadXML(source, styleFile);
    ASSERT_CPP(success, "load XML failed ");

    CreateChildren();
    Update();

    return success;
}

void TabSelector::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

}


void TabSelector::Update()
{
    ASSERT_CPP(cursor_!=nullptr,  "can not found unselect_cursor");

    if(IsSelected())
    {
        auto* cache = GetSubsystem<ResourceCache>(); 
        auto texture = cache->GetResource<Texture2D>(selectCursorTexture_);
        ASSERT_CPP(texture!=nullptr, " can not load texture  for select cursor with name ", selectCursorTexture_.CString());
        cursor_->SetTexture(texture);
    }
    else
    {
        auto* cache = GetSubsystem<ResourceCache>(); 
        auto texture = cache->GetResource<Texture2D>(unselectCursorTexture_);
        ASSERT_CPP(texture!=nullptr, " can not load texture  for unselect cursor with name ", unselectCursorTexture_.CString());
        cursor_->SetTexture(texture);
    }
    
    Vector2 pos = cursorBasePosition_;
    pos.x_+= index_*cursor_->GetWidth();
    cursor_->SetPosition(pos);
    
    for(auto& txt : tabs_)
    for(auto i =0;i<tabs_.Size(); i++)
    {
        auto& txt = tabs_[i];
        txt->SetColor(unselectColor_);
        auto x = (cursor_->GetWidth()-txt->GetWidth())/2;
        auto y = (cursor_->GetHeight()-txt->GetHeight())/2;
        txt->SetPosition(cursorBasePosition_.x_+i*cursor_->GetWidth()+x
                        ,cursorBasePosition_.y_+y);
    }
    
    {
        ASSERT_CPP(index_<tabs_.Size(), "index_ is not correct ", index_, "/", tabs_.Size());
        auto& txt = tabs_[index_];
        txt->SetColor(selectColor_);
    } 

}

bool TabSelector::HandleKeyDown(InputKey key)
{
    if(!IsSelected()) return false;

    if(     key == InputKey::UP_1P
        ||  key == InputKey::DOWN_1P
        )
    {
        SetSelected(false);
        Update();
        using namespace LostSelected;
        VariantMap& eventData = GetEventDataMap();
        eventData[P_ELEMENT] = this;
        eventData[P_KEY]    = int(key);
        SendEvent(E_LOSTSELECTED, eventData);
        return true;
    }

    bool indexChanged = false;
    bool handledKey = false;
    if(key == InputKey::LEFT_1P) 
    {
        LOG_INFOS_CPP(" LEFT");
        if(index_>0)
        {
            indexChanged = true;
            index_--; 
        }
        handledKey = true;
    }
    else if(key == InputKey::RIGHT_1P)
    {
        LOG_INFOS_CPP(" RIGHT");
        if(index_<tabs_.Size()-1) 
        {
            indexChanged = true;
            index_++;
        }
        handledKey = true;
    }

    if(indexChanged)
    {
        Update();
        using namespace ItemChanged;
        VariantMap& eventData = GetEventDataMap();
        eventData[P_ELEMENT] = this;
        eventData[P_INDEX] = index_;
        SendEvent(E_ITEMCHANGED, eventData);
    }

    return (handledKey);
}

void TabSelector::CreateChildren()
{

    RemoveAllChildren();

    {
        auto texture = CACHE->GetResource<Texture2D>(backgroundTexture_);
        ASSERT_CPP(texture!=nullptr, " can not load texture  for background with name ", backgroundTexture_.CString());
        auto* bg = this->CreateChild<Sprite>(String("background"));
        bg->SetSize(texture->GetWidth(), texture->GetHeight());
        bg->SetTexture(texture);
        bg->SetBlendMode(BLEND_ALPHA);
    }

    {
        auto texture = CACHE->GetResource<Texture2D>(unselectCursorTexture_);
        ASSERT_CPP(texture!=nullptr, " can not load texture  for unselect cursor with name ", unselectCursorTexture_.CString());
        cursor_ = this->CreateChild<Sprite>(String("cursor"));
        cursor_->SetSize(texture->GetWidth(), texture->GetHeight());
        cursor_->SetTexture(texture);
        cursor_->SetBlendMode(BLEND_ALPHA);
        cursor_->SetPosition(cursorBasePosition_);
    }

    {
        auto totalTabs = texts_.Size();
        auto tabWidth = cursor_->GetWidth();
        auto tabHeight= cursor_->GetHeight();
        auto font = CACHE->GetResource<Font>(textFont_);
        tabs_.Clear();
        for(auto i = 0;i<totalTabs ; i++)
        {
            auto text = this->CreateChild<Text>();
            text->SetPosition(cursorBasePosition_.x_+i*tabWidth,  cursorBasePosition_.y_);
            //text->SetSize(tabWidth, tabHeight);
            text->SetTextAlignment(HA_CENTER);
            text->SetFont(font, textFontSize_);
            text->SetColor(unselectColor_);
            LOG_INFOS_CPP(" textAutoLocalization_ ", textAutoLocalization_);
            text->SetAutoLocalizable(textAutoLocalization_);
            text->SetText(texts_[i]);
            WeakPtr<Text>  ptext { text};
            ASSERT_CPP(ptext!=nullptr, " txt is nullptr");
            tabs_.Push(ptext);
        }
    }
}

}

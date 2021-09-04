

//
// Copyright (c) 2008-2016 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/UI/BorderImage.h>
#include <Urho3D/UI/CheckBox.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLElement.h>
#include <Urho3D/Input/InputEvents.h>

#include "Gamelist.hpp"
#include "../utils/log.hpp"
#include "../utils/string.hpp"
#include "../InputSystem.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

#include <Urho3D/DebugNew.h>
//=============================================================================
//=============================================================================
void Gamelist::RegisterObject(Context* context)
{
    context->RegisterFactory<Gamelist>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);

    URHO3D_ATTRIBUTE("Page Items", int, pageItems_, 10, AM_FILE);
    URHO3D_ATTRIBUTE("Item Gap",   int, pageItems_,  3, AM_FILE);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("List Mask Texture", GetListMaskTextureAttr, SetListMaskTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("List Mask Select Texture", GetListMaskSelectTextureAttr, SetListMaskSelectTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("List Icon Default Texture", GetListIconDefaultTextureAttr, SetListIconDefaultTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Item Background Texture", GetItemBackgroundTextureAttr, SetItemBackgroundTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Item Background Select Texture", GetItemBackgroundSelectTextureAttr, SetItemBackgroundSelectTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Select Color", Color, selectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_ATTRIBUTE("UnSelect Color", Color, unselectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Text Font", GetTextFontAttr, SetTextFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Text Font Size", float, textFontSize_, DEFAULT_FONT_SIZE, AM_FILE);

    URHO3D_ATTRIBUTE("Item Base Position", Vector2, itemBasePosition_, Vector2::ZERO, AM_FILE);
    URHO3D_ATTRIBUTE("List Icon Size", IntVector2, listIconSize_, IntVector2::ZERO, AM_FILE);

}

Gamelist::Gamelist(Context *context)
    : UIElement(context)
{
}

bool Gamelist::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    bool success = UIElement::LoadXML(source, styleFile);
    ASSERT_CPP(success, "load XML failed ");

    // 
//    UIItems_.Clear();
//    for(auto&& c : GetChildren())
//    {
//        WeakPtr<UIElement>  item { static_cast<UIElement*>(c.Get())};
//        ASSERT_CPP(item!=nullptr, " element is nullptr");
//        UIItems_.Push(item);
//    }
//    ASSERT_CPP(UIItems_.Size()==pageItems_, "page Items ", UIItems_.Size(), "/", pageItems_);
//
    CreateChildren();
    Update();

    return success;
}

void Gamelist::Update()
{
    // set all UIItems_;
    for(auto& item : UIItems_) {item->SetVisible(false);}
    auto totalGames = games_.size();
    LOG_INFOS_CPP(" t ", index_, totalGames, pageItems_ );
    for(auto t=index_; t<totalGames && t<index_+pageItems_ ; t++)
    {
        LOG_INFOS_CPP(" t ", t );
        auto itemIndex = t-index_; 
        ASSERT_CPP(itemIndex < UIItems_.Size(), "itemIndex is not correct", itemIndex, UIItems_.Size());
        UIItems_[itemIndex]->SetVisible(true);
        auto thumbnailPath = games_[t]->thumbnailPath_;
        auto name          = games_[t]->name_;
        {
            auto sprite  = UIItems_[itemIndex]->GetChildStaticCast<Sprite>(String("Thumbnail"));
            ASSERT_CPP(sprite!=nullptr, "can not find Thumbnail ");
            if(context_->GetSubsystem<FileSystem>()->FileExists(thumbnailPath))
            {
                // load texture and set  
                File file(context_, thumbnailPath);
                auto texture = new Texture2D(context_);
                auto success = texture->Load(file);
                ASSERT_CPP(success, " load texture2D failed ", thumbnailPath.CString());
                sprite->SetTexture(texture);
                auto width = texture->GetWidth();
                auto height= texture->GetHeight();
                LOG_INFOS_CPP(width, height);


                IntRect imageRect(0, 0, width, height);
                sprite->SetImageRect(imageRect);
                //sprite->SetSize(width, height);
                
            }
        }
        {
            auto s = string_format("%04d %s", t+1, name.CString());
            UIItems_[itemIndex]->GetChildStaticCast<Text>(String("name"))->SetText(ToString(s.c_str()));
        }
    }

}

bool Gamelist::HandleKeyDown(InputKey key)
{
    return false;
}

void Gamelist::addItem(const Item& item)
{
    auto newItem = std::make_unique<Item>(item);
    games_.push_back(std::move(newItem));
}

void Gamelist::CreateChildren()
{
    RemoveAllChildren();
    auto* cache = GetSubsystem<ResourceCache>(); 
    UIItems_.Clear();
    auto listMaskTexture = cache->GetResource<Texture2D>(listMaskTexture_);
    for(auto i = 0;i<pageItems_ ;i++)
    {
        auto* item = CreateChild<UIElement>();
        item->SetPosition(0, (listMaskTexture->GetHeight()+itemGap_)*i);
        auto listMark = item->CreateChild<Sprite>(String("listMark"));
        {
            auto texture = cache->GetResource<Texture2D>(listMaskTexture_);
            LOG_INFOS_CPP(texture!=nullptr, " can not open texture2d with name ", listMaskTexture_.CString());
            listMark ->SetSize(texture->GetWidth(), texture->GetHeight());
            listMark ->SetTexture(texture);
            listMark ->SetBlendMode(BLEND_ALPHA);
        }
        {
            auto texture = cache->GetResource<Texture2D>(listIconDefaultTexture_);
            LOG_INFOS_CPP(texture!=nullptr, " can not open texture2d with name ", listIconDefaultTexture_.CString());
            auto listIcon = item->CreateChild<Sprite>(String("listIcon"));
            listIcon ->SetTexture(texture);
            listIcon ->SetSize(listIconSize_);
            listIcon ->SetBlendMode(BLEND_ALPHA);
            listIcon ->SetPosition(listMark->GetWidth(), 0);
        }
        {
            auto texture = cache->GetResource<Texture2D>(itemBackgroundTexture_);
            LOG_INFOS_CPP(texture!=nullptr, " can not open texture2d with name ", itemBackgroundTexture_.CString());
            auto cursor = item->CreateChild<Sprite>(String("cursor"));
            cursor ->SetSize(texture->GetWidth(), texture->GetHeight());
            cursor ->SetTexture(texture);
            cursor ->SetBlendMode(BLEND_ALPHA);
            cursor ->SetPosition(itemBasePosition_);
        }
        {
            auto name = item->CreateChild<Text>(String("name"));
            auto font = cache->GetResource<Font>(textFont_);
            name->SetTextAlignment(HA_CENTER);
            name->SetFont(font, textFontSize_);
            name->SetColor(unselectColor_);
        }
        WeakPtr<UIElement>  pitem { item};
        UIItems_.Push(pitem);
    }

}

}

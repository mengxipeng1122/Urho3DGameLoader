
#include "../utils/log.hpp"
#include "../utils/string.hpp"
#include "../InputSystem.hpp"

#include "Gamelist.hpp"

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
    for(auto t=index_; t<totalGames && t<index_+pageItems_ ; t++)
    {
        auto itemIndex = t-index_; 
        ASSERT_CPP(itemIndex < UIItems_.Size(), "itemIndex is not correct", itemIndex, UIItems_.Size());
        UIItems_[itemIndex]->SetVisible(true);
        auto thumbnailPath = games_[t]->thumbnailPath_;
        auto name          = games_[t]->name_;
        {
            auto sprite  = UIItems_[itemIndex]->GetChildStaticCast<Sprite>(String("listIcon"));
            ASSERT_CPP(sprite!=nullptr, "can not find list Icon");
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
            }
        }
        {
            auto s = string_format("%04d %s", t+1, name.CString());
            UIItems_[itemIndex]->GetChildStaticCast<Text>(String("name"))->SetText(ToString(s.c_str()));
        }
        {
            auto* cursor =  UIItems_[itemIndex]->GetChildStaticCast<Sprite>(String("cursor"));
            auto* txt    =  UIItems_[itemIndex]->GetChildStaticCast<Text>  (String("name"));
            auto x = (cursor->GetWidth() -txt->GetWidth())/2;
            auto y = (cursor->GetHeight()-txt->GetHeight())/2;
            auto cursorPosition = cursor->GetPosition();
            txt->SetPosition(cursorPosition.x_+3
                        ,cursorPosition.y_+y);
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
    UIItems_.Clear();
    auto listMaskTexture = CACHE->GetResource<Texture2D>(listMaskTexture_);
    ASSERT_CPP(listMaskTexture != nullptr, " load Texture2D of ", listMaskTexture_.CString(), "failed");
    for(auto i = 0;i<pageItems_ ;i++)
    {
        auto* item = CreateChild<UIElement>();
        item->SetPosition(0, (listMaskTexture->GetHeight()+itemGap_)*i);
        auto listMark = item->CreateChild<Sprite>(String("listMark"));
        {
            auto texture = CACHE->GetResource<Texture2D>(listMaskTexture_);
            ASSERT_CPP(texture!=nullptr, " can not open texture2d with name ", listMaskTexture_.CString());
            listMark ->SetSize(texture->GetWidth(), texture->GetHeight());
            listMark ->SetTexture(texture);
            listMark ->SetBlendMode(BLEND_ALPHA);
        }
        {
            auto texture = CACHE->GetResource<Texture2D>(listIconDefaultTexture_);
            ASSERT_CPP(texture!=nullptr, " can not open texture2d with name ", listIconDefaultTexture_.CString());
            auto listIcon = item->CreateChild<Sprite>(String("listIcon"));
            listIcon ->SetTexture(texture);
            listIcon ->SetSize(listIconSize_);
            listIcon ->SetBlendMode(BLEND_ALPHA);
            listIcon ->SetPosition(listMark->GetWidth(), 0);
        }
        {
            auto texture = CACHE->GetResource<Texture2D>(itemBackgroundTexture_);
            ASSERT_CPP(texture!=nullptr, " can not open texture2d with name ", itemBackgroundTexture_.CString());
            auto cursor = item->CreateChild<Sprite>(String("cursor"));
            cursor ->SetSize(texture->GetWidth(), texture->GetHeight());
            cursor ->SetTexture(texture);
            cursor ->SetBlendMode(BLEND_ALPHA);
            cursor ->SetPosition(itemBasePosition_);
        }
        {
            auto name = item->CreateChild<Text>(String("name"));
            auto font = CACHE->GetResource<Font>(textFont_);
            name->SetTextAlignment(HA_CENTER);
            name->SetFont(font, textFontSize_);
            name->SetColor(unselectColor_);
        }
        WeakPtr<UIElement>  pitem { item};
        UIItems_.Push(pitem);
    }

}

}

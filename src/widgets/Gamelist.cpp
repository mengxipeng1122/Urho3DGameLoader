
#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "Gamelist.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//#include <Urho3D/DebugNew.h>
//=============================================================================
//=============================================================================
void Gamelist::RegisterObject(Context* context)
{
    context->RegisterFactory<Gamelist>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Widget);

    URHO3D_ATTRIBUTE("Page Items", int, pageItems_, 10, AM_FILE);
    URHO3D_ATTRIBUTE("Item Gap",   int, pageItems_,  3, AM_FILE);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("List Mask Texture", GetListMaskTextureAttr, SetListMaskTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("List Mask Select Texture", GetListMaskSelectTextureAttr, SetListMaskSelectTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("List Icon Default Texture", GetListIconDefaultTextureAttr, SetListIconDefaultTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Item Background Texture", GetItemBackgroundTextureAttr, SetItemBackgroundTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Item Background Select Texture", GetItemBackgroundSelectTextureAttr, SetItemBackgroundSelectTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Select Color", Color, selectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_ATTRIBUTE("Unselect Color", Color, unselectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Text Font", GetTextFontAttr, SetTextFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Text Font Size", float, textFontSize_, DEFAULT_FONT_SIZE, AM_FILE);

    URHO3D_ATTRIBUTE("Item Base Position", Vector2, itemBasePosition_, Vector2::ZERO, AM_FILE);
    URHO3D_ATTRIBUTE("List Icon Size", IntVector2, listIconSize_, IntVector2::ZERO, AM_FILE);

}

Gamelist::Gamelist(Context *context)
    : Widget(context)
{
}

// bool Gamelist::LoadXML(const XMLElement& source, XMLFile* styleFile)
// {
//     bool success = UIElement::LoadXML(source, styleFile);
//     ASSERT_CPP(success, "load XML failed ");
// 
//     // 
// //    UIItems_.Clear();
// //    for(auto&& c : GetChildren())
// //    {
// //        WeakPtr<UIElement>  item { static_cast<UIElement*>(c.Get())};
// //        ASSERT_CPP(item!=nullptr, " element is nullptr");
// //        UIItems_.Push(item);
// //    }
// //    ASSERT_CPP(UIItems_.Size()==pageItems_, "page Items ", UIItems_.Size(), "/", pageItems_);
// //
//     CreateChildren();
//     //Update();
// 
//     return success;
// }

//void Gamelist::Update()
//{
//    // set all UIItems_;
//    for(auto& item : UIItems_) {item->SetVisible(false);}
//    auto totalGames = games_.Size();
//
//    LOG_INFOS_CPP(" firstIndex_ ", firstIndex_ , " index_", index_);
//    
//    for(auto t=0; t<pageItems_ ; t++)
//    {
//        auto gameIndex = firstIndex_+t;
//        if(gameIndex>=totalGames) {
//            UIItems_[t]->SetVisible(false);
//            continue;
//        }
//        ASSERT_CPP(gameIndex>=0 && gameIndex < games_.Size(), "gameIndex is not correct", gameIndex, UIItems_.Size());
//        UIItems_[t]->SetVisible(true);
//        auto iconPath = games_[gameIndex]->iconPath_;
//        auto name     = games_[gameIndex]->name_;
//        {
//            auto texture = CACHE->GetResource<Texture2D>(listMaskTexture_);
//            UIItems_[t]->GetChildStaticCast<Sprite>(String("listMark"))->SetTexture(texture);
//        }
//        {
//            auto sprite  = UIItems_[t]->GetChildStaticCast<Sprite>(String("listIcon"));
//            ASSERT_CPP(sprite!=nullptr, "can not find list Icon");
//            if(context_->GetSubsystem<FileSystem>()->FileExists(iconPath))
//            {
//                // load texture and set  
//                File file(context_, iconPath);
//                auto texture = new Texture2D(context_);
//                auto success = texture->Load(file);
//                ASSERT_CPP(success, " load texture2D failed ", iconPath.CString());
//                sprite->SetTexture(texture);
//                auto width = texture->GetWidth();
//                auto height= texture->GetHeight();
//                IntRect imageRect(0, 0, width, height);
//                sprite->SetImageRect(imageRect);
//            }
//        }
//        {
//            auto s = ConstructStringWithFormat("%04d %s", gameIndex+1, name.CString());
//            UIItems_[t]->GetChildStaticCast<Text>(String("name"))->SetText(ToString(s.c_str()));
//        }
//        {
//            auto texture = CACHE->GetResource<Texture2D>(itemBackgroundTexture_);
//            UIItems_[t]->GetChildStaticCast<Sprite>(String("cursor"))->SetTexture(texture);
//        }
//        {
//            auto* cursor =  UIItems_[t]->GetChildStaticCast<Sprite>(String("cursor"));
//            auto* txt    =  UIItems_[t]->GetChildStaticCast<Text>  (String("name"));
//            auto x = (cursor->GetWidth() -txt->GetWidth())/2;
//            auto y = (cursor->GetHeight()-txt->GetHeight())/2;
//            auto cursorPosition = cursor->GetPosition();
//            txt->SetPosition(cursorPosition.x_+3 ,cursorPosition.y_+y);
//            txt->SetColor(unselectColor_);
//        }
//
//        if(t == index_ && IsSelected())
//        {
//            {
//                auto texture = CACHE->GetResource<Texture2D>(listMaskSelectTexture_);
//                UIItems_[t]->GetChildStaticCast<Sprite>(String("listMark"))->SetTexture(texture);
//            }
//            {
//                auto texture = CACHE->GetResource<Texture2D>(itemBackgroundSelectTexture_);
//                UIItems_[t]->GetChildStaticCast<Sprite>(String("cursor"))->SetTexture(texture);
//            }
//            {
//                auto* txt    =  UIItems_[t]->GetChildStaticCast<Text>  (String("name"));
//                txt->SetColor(selectColor_);
//            }
//        }
//
//    }
//
//
//}

bool Gamelist::HandleKeyDown(InputKey key, int idx)
{
    if(!IsSelected()) return false;


    if(key == InputKey::START)
    {
        SetSelected(false);
        //Update();
        Widget::SendLostSelectedEvent(key, idx);
        return true;
    }

    bool indexChanged = false;
    bool handledKey = false;
    auto totalGames = games_.Size();
    if(key == InputKey::LEFT) 
    {
        LOG_INFOS_CPP(" LEFT");
        goPreviousPage();
        indexChanged = true;
        handledKey = true;
    }
    else if(key == InputKey::RIGHT)
    {
        LOG_INFOS_CPP(" RIGHT");
        goNextPage();
        indexChanged = true;
        handledKey = true;
    }
    else if(key == InputKey::UP)
    {
        goPreviousItem();
        indexChanged = true;
        handledKey = true;
    }
    else if(key == InputKey::DOWN)
    {
        goNextItem();
        indexChanged = true;
        handledKey = true;
    }

    if(indexChanged)
    {
        //Update();
        Widget::SendItemChangedEvent(firstIndex_+index_);
    }
    
    return handledKey;
}

void Gamelist::AddItem(const Item& item)
{
    games_.Push(item);
}

// void Gamelist::CreateChildren()
// {
//     RemoveAllChildren();
//     UIItems_.Clear();
//     auto listMaskTexture = CACHE->GetResource<Texture2D>(listMaskTexture_);
//     ASSERT_CPP(listMaskTexture != nullptr, " load Texture2D of ", listMaskTexture_.CString(), "failed");
//     for(auto i = 0;i<pageItems_ ;i++)
//     {
//         auto* item = CreateChild<UIElement>();
//         item->SetPosition(0, (listMaskTexture->GetHeight()+itemGap_)*i);
//         auto listMark = item->CreateChild<Sprite>(String("listMark"));
//         {
//             auto texture = CACHE->GetResource<Texture2D>(listMaskTexture_);
//             ASSERT_CPP(texture!=nullptr, " can not open texture2d with name ", listMaskTexture_.CString());
//             listMark ->SetSize(texture->GetWidth(), texture->GetHeight());
//             listMark ->SetTexture(texture);
//             listMark ->SetBlendMode(BLEND_ALPHA);
//         }
//         {
//             auto texture = CACHE->GetResource<Texture2D>(listIconDefaultTexture_);
//             ASSERT_CPP(texture!=nullptr, " can not open texture2d with name ", listIconDefaultTexture_.CString());
//             auto listIcon = item->CreateChild<Sprite>(String("listIcon"));
//             listIcon ->SetTexture(texture);
//             listIcon ->SetSize(listIconSize_);
//             listIcon ->SetBlendMode(BLEND_ALPHA);
//             listIcon ->SetPosition(listMark->GetWidth(), 0);
//         }
//         {
//             auto texture = CACHE->GetResource<Texture2D>(itemBackgroundTexture_);
//             ASSERT_CPP(texture!=nullptr, " can not open texture2d with name ", itemBackgroundTexture_.CString());
//             auto cursor = item->CreateChild<Sprite>(String("cursor"));
//             cursor ->SetSize(texture->GetWidth(), texture->GetHeight());
//             cursor ->SetTexture(texture);
//             cursor ->SetBlendMode(BLEND_ALPHA);
//             cursor ->SetPosition(itemBasePosition_);
//         }
//         {
//             auto name = item->CreateChild<Text>(String("name"));
//             auto font = CACHE->GetResource<Font>(textFont_);
//             name->SetTextAlignment(HA_CENTER);
//             name->SetFont(font, textFontSize_);
//             name->SetColor(unselectColor_);
//         }
//         WeakPtr<UIElement>  pitem { item};
//         UIItems_.Push(pitem);
//     }
// 
// }


int Gamelist::goPreviousItem()
{
    index_--;
    if(index_<0) {
        index_ = pageItems_-1;
        firstIndex_-=pageItems_;
        if(firstIndex_<0) {
            firstIndex_ = ((games_.Size()-1)/pageItems_)*pageItems_;
            if(firstIndex_+index_>=(int)games_.Size()) { index_ = games_.Size()-1-firstIndex_; }
        }
    }
    UpdateDrawItems();
    return 0;
}

int Gamelist::goNextItem()
{
    if(firstIndex_+index_+1>=(int)games_.Size())
    {
        firstIndex_ = 0;
        index_ = 0;
        return -1;

    }

    index_++;
    if(index_>=pageItems_) { 
        index_=0; 
        firstIndex_+=pageItems_;
        if(firstIndex_>=(int)games_.Size()) { firstIndex_=0; }
        if(firstIndex_+index_>=(int)games_.Size()) { index_ = games_.Size()-1-firstIndex_; }
    }
    UpdateDrawItems();
    return 0;
}

int Gamelist::goPreviousPage() 
{
    firstIndex_-=pageItems_;
    if(firstIndex_<0) {
        firstIndex_ = ((games_.Size()-1)/pageItems_)*pageItems_;
        if(firstIndex_+index_>=(int)games_.Size()) { index_ = games_.Size()-1-firstIndex_; }
    }
    UpdateDrawItems();
    return 0;
}

int Gamelist::goNextPage()     
{
    firstIndex_+=pageItems_;
    if(firstIndex_>=(int)games_.Size()) { firstIndex_=0; }
    if(firstIndex_+index_>=(int)games_.Size()) { index_ = games_.Size()-1-firstIndex_; }
    UpdateDrawItems();
    return 0;
}


void Gamelist::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    // draw background
    const auto listMaskTexture = CACHE->GetResource<Texture2D>(listMaskTexture_);
    const auto listMaskSelectTexture = CACHE->GetResource<Texture2D>(listMaskSelectTexture_);
    const auto itemHeight = listMaskTexture->GetHeight();
    for(auto i = 0; i<drawItems_.Size(); i++) {
        const auto& item = drawItems_[i];
        // draw list mark
        {
            Widget::AddTextureBatch(batches, vertexData, currentScissor, item.listMaskTexture_, item.listMaskPosition_.x_, item.listMaskPosition_.y_);
        }
        
        // draw icon
        {
            Widget::AddTextureBatch(batches, vertexData, currentScissor, item.iconTexture_, item.iconPosition_.x_, item.iconPosition_.y_, listIconSize_.x_, listIconSize_.y_ );
        }

        // draw background
        {
            Widget::AddTextureBatch(batches, vertexData, currentScissor, item.listBackgroundTexture_, item.listBackgroundPosition_.x_, item.listBackgroundPosition_.y_);
        }

        // draw name
        {
            Widget::AddStringBatch(batches, vertexData, currentScissor, item.no_, item.noFace_, item.noColor_, item.noPosition_.x_, item.noPosition_.y_);
        }
    }
}

void Gamelist::UpdateDrawItems()
{
    drawItems_.Clear();
    for(auto i = 0; i+firstIndex_<games_.Size() && i<pageItems_; i++) {
        DrawItem newItem;
        auto selected = IsSelected() && i == index_;
        auto* listMaskTexture = CACHE->GetResource<Texture2D>(listMaskTexture_);
        const auto  itemHeight = listMaskTexture->GetHeight();
        {
            auto* listMaskSelectTexture = CACHE->GetResource<Texture2D>(listMaskSelectTexture_);
            newItem.listMaskPosition_.x_ = 0;
            newItem.listMaskPosition_.y_ = i*(itemHeight+itemGap_);
            newItem.listMaskTexture_ = selected ? listMaskSelectTexture : listMaskTexture;
        }
        {
            auto* texture = [&](){
                    const auto& iconPath = games_[firstIndex_+i].iconPath_;
                    if(context_->GetSubsystem<FileSystem>()->FileExists(iconPath)){
                        auto texture = new Texture2D(context_);
                        File iconFile(context_, iconPath);
                        texture->Load(iconFile);
                        return texture;
                    } 
                    else {
                        return CACHE->GetResource<Texture2D>(listIconDefaultTexture_);
                    }
                } ();
            ASSERT_CPP(texture!=nullptr, "can not get texture for game ", i+firstIndex_);
            newItem.iconPosition_.x_ = listMaskTexture->GetWidth();
            newItem.iconPosition_.y_ = i*(itemHeight+itemGap_);
            newItem.iconTexture_ = texture;
        }
        {
            auto* itemBackgroundTexture = CACHE->GetResource<Texture2D>(itemBackgroundTexture_);
            auto* itemBackgroundSelectTexture = CACHE->GetResource<Texture2D>(itemBackgroundSelectTexture_);
            newItem.listBackgroundPosition_.x_ = itemBasePosition_.x_;
            newItem.listBackgroundPosition_.y_ = i*(itemHeight+itemGap_) + itemBasePosition_.y_;
            newItem.listBackgroundTexture_ = selected ?  itemBackgroundSelectTexture : itemBackgroundTexture;
        }
        {
            auto font = CACHE->GetResource<Font>(textFont_);
            FontFace* face = font->GetFace(textFontSize_);
            newItem.noFace_ = face;
            auto no  = i+firstIndex_+1;
            String name{"0000"};
            name[0] = ((no/1000)%10) + '0';
            name[1] = ((no/100 )%10) + '0';
            name[2] = ((no/10  )%10) + '0';
            name[3] = ((no/1   )%10) + '0';
            const auto& gameName = games_[i+firstIndex_].name_;
            name += " ";
            name += gameName;
            newItem.no_ =name;
            LOG_INFOS_CPP(gameName, name);
            auto offsety = (listMaskTexture->GetHeight()-face->GetRowHeight())/2;
            newItem.noPosition_.x_ = itemBasePosition_.x_+offsety;
            newItem.noPosition_.y_ = i*(itemHeight+itemGap_)+itemBasePosition_.y_+offsety;
            newItem.noColor_ = selected ? selectColor_ : unselectColor_;
        }
        drawItems_.Push(newItem);
    }
}

}

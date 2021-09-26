
#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "WifiList.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//#include <Urho3D/DebugNew.h>
//=============================================================================
//=============================================================================
void WifiList::RegisterObject(Context* context)
{
    context->RegisterFactory<WifiList>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Widget);

    URHO3D_ATTRIBUTE("Page Items", int, pageItems_, 10, AM_FILE);
    URHO3D_ATTRIBUTE("Item Gap",   int, pageItems_,  3, AM_FILE);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Background Texture", GetBackgroundTextureAttr, SetBackgroundTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Select Background Texture", GetSelectBackgroundTextureAttr, SetSelectBackgroundTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Wifi Signal Strength 0 Texture", GetWifiSignalStrength0TextureAttr, SetWifiSignalStrength0TextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Wifi Signal Strength 1 Texture", GetWifiSignalStrength1TextureAttr, SetWifiSignalStrength1TextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Wifi Signal Strength 2 Texture", GetWifiSignalStrength2TextureAttr, SetWifiSignalStrength2TextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Wifi Signal Strength 3 Texture", GetWifiSignalStrength3TextureAttr, SetWifiSignalStrength3TextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Wifi Password Texture", GetWifiPasswordTextureAttr, SetWifiPasswordTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Select Color", Color, selectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_ATTRIBUTE("Unselect Color", Color, unselectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Text Font", GetTextFontAttr, SetTextFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Text Font Size", float, textFontSize_, DEFAULT_FONT_SIZE, AM_FILE);


}

WifiList::WifiList(Context *context)
    : Widget(context)
{
}


bool WifiList::HandleKeyDown(InputKey key, int idx)
{
    if(!IsSelected()) return false;



    bool indexChanged = false;
    bool handledKey = false;
    auto totalGames = aps_.Size();
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
    }
    
    return handledKey;
}

void WifiList::AddItem(const Item& item)
{
    aps_.Push(item);
}


int WifiList::goPreviousItem()
{
    index_--;
    if(index_<0) {
        index_ = pageItems_-1;
        firstIndex_-=pageItems_;
        if(firstIndex_<0) {
            firstIndex_ = ((aps_.Size()-1)/pageItems_)*pageItems_;
            if(firstIndex_+index_>=(int)aps_.Size()) { index_ = aps_.Size()-1-firstIndex_; }
        }
    }
    return 0;
}

int WifiList::goNextItem()
{
    if(firstIndex_+index_+1>=(int)aps_.Size())
    {
        firstIndex_ = 0;
        index_ = 0;
        return -1;

    }

    index_++;
    if(index_>=pageItems_) { 
        index_=0; 
        firstIndex_+=pageItems_;
        if(firstIndex_>=(int)aps_.Size()) { firstIndex_=0; }
        if(firstIndex_+index_>=(int)aps_.Size()) { index_ = aps_.Size()-1-firstIndex_; }
    }
    return 0;
}

int WifiList::goPreviousPage() 
{
    firstIndex_-=pageItems_;
    if(firstIndex_<0) {
        firstIndex_ = ((aps_.Size()-1)/pageItems_)*pageItems_;
        if(firstIndex_+index_>=(int)aps_.Size()) { index_ = aps_.Size()-1-firstIndex_; }
    }
    return 0;
}

int WifiList::goNextPage()     
{
    firstIndex_+=pageItems_;
    if(firstIndex_>=(int)aps_.Size()) { firstIndex_=0; }
    if(firstIndex_+index_>=(int)aps_.Size()) { index_ = aps_.Size()-1-firstIndex_; }
    return 0;
}


void WifiList::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    // draw background
    for(auto i=0;i<pageItems_; i++) {
        auto selected = i+firstIndex_ == index_;
        if(selected) {
            auto* texture = CACHE->GetResource<Texture2D>(selectBackgroundTexture_);
            Widget::AddTextureBatch(batches, vertexData, currentScissor, texture, 0, (texture->GetHeight()+itemGap_)*i);
        }
        else{
            auto* texture = CACHE->GetResource<Texture2D>(backgroundTexture_);
            Widget::AddTextureBatch(batches, vertexData, currentScissor, texture, 0, (texture->GetHeight()+itemGap_)*i);
        }
    }
}

}



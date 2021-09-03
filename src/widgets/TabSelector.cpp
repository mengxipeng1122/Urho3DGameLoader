
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
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLElement.h>
#include <Urho3D/Input/InputEvents.h>

#include "TabSelector.hpp"
#include "../utils/log.hpp"
#include "../utils/string.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

#include <Urho3D/DebugNew.h>
//=============================================================================
//=============================================================================
void TabSelector::RegisterObject(Context* context)
{
    context->RegisterFactory<TabSelector>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);

    URHO3D_ATTRIBUTE("Tab Gap", int , tabGap_, 40, AM_FILE);
    URHO3D_ATTRIBUTE("Select Color", Color, selectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_ATTRIBUTE("UnSelect Color", Color, unselectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
}

TabSelector::TabSelector(Context *context)
    : UIElement(context)
{
}


void TabSelector::Quit()
{
    UnsubscribeFromEvent(E_UPDATE);
}

bool TabSelector::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    bool success = UIElement::LoadXML(source, styleFile);
    ASSERT_CPP(success, "load XML failed ");

    tabs_.Clear();
    // get tabs
    for(auto&& c : GetChildren())
    { 
        if(c->GetType() ==  Text::GetTypeStatic())
        {
            WeakPtr<Text>  txt { static_cast<Text*>(c.Get())};
            ASSERT_CPP(txt!=nullptr, " txt is nullptr");
            tabs_.Push(txt);
        }
    }
    LOG_INFOS_CPP("tabs_", tabs_.Size());

    unselectCursor_ = static_cast<Sprite*>(GetChild(String("unselect_cursor")));
    ASSERT_CPP(unselectCursor_!=nullptr,  "can not found unselect_cursor");

    selectCursor_ = static_cast<Sprite*>(GetChild(String("select_cursor")));
    ASSERT_CPP(unselectCursor_!=nullptr,  "can not found select_cursor");

    // get base position
    cursorBasePosition = selectCursor_->GetPosition();

    Update();

    return success;
}

void TabSelector::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

}


void TabSelector::Update()
{
    ASSERT_CPP(unselectCursor_!=nullptr,  "can not found unselect_cursor");
    ASSERT_CPP(selectCursor_!=nullptr,  "can not found unselect_cursor");

    unselectCursor_->SetVisible(!focusing_);
    selectCursor_->SetVisible(focusing_);

    Vector2 pos = cursorBasePosition;
    pos.x_+= index_*tabGap_;
    if(focusing_) selectCursor_->SetPosition(pos);
    else unselectCursor_->SetPosition(pos);

    for(auto& txt : tabs_)
    {
        txt->SetColor(unselectColor_);
    }

    {
        ASSERT_CPP(index_<tabs_.Size(), "index_ is not correct ", index_, "/", tabs_.Size());
        auto& txt = tabs_[index_];
        txt->SetColor(selectColor_);
        
    } 

}

bool TabSelector::HandleKeyDown(InputKey key)
{
    if(key == InputKey::LEFT_1P) 
    {
        LOG_INFOS_CPP(" LEFT");
        if(index_>0) index_--; 


        using namespace TabChanged;
        VariantMap& eventData = GetEventDataMap();
        eventData[P_ELEMENT] = this;
        eventData[P_INDEX] = index_;
        SendEvent(E_TABCHANGED, eventData);
        Update(); return true; 
    }
    else if(key == InputKey::RIGHT_1P)
    {
        LOG_INFOS_CPP(" RIGHT");
        if(index_<tabs_.Size()-1) index_++; Update(); return true; 
    }
    return false;
}

}

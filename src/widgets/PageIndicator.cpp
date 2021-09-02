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

#include "PageIndicator.hpp"
#include "../utils/log.hpp"
#include "../utils/string.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

#include <Urho3D/DebugNew.h>
//=============================================================================
//=============================================================================
void PageIndicator::RegisterObject(Context* context)
{
    context->RegisterFactory<PageIndicator>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);
}

PageIndicator::PageIndicator(Context *context)
    : UIElement(context)
{
}


void PageIndicator::Quit()
{
    UnsubscribeFromEvent(E_UPDATE);
}

bool PageIndicator::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    bool success = UIElement::LoadXML(source, styleFile);
    ASSERT_CPP(success, "load XML failed ");
    // get bg
    bg_   = static_cast<Sprite*>(GetChild(String("bg")));
    ASSERT_CPP(bg_!=nullptr, " can not found bg ");
    text_ = static_cast<Text*>(GetChild(String("text")));
    ASSERT_CPP(text_!=nullptr, " can not found text ");
    SetText();

    return success;
}

void PageIndicator::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

}

void PageIndicator::SetText()
{
    ASSERT_CPP(text_!=nullptr, " can not get text");
    LOG_INFOS_CPP(" go here ");
    std::string s = string_format("%03d/%04d",curPageNo_, totalPageNo_);
    text_->SetText(ToString(s.c_str()));
}


void PageIndicator::Update()
{
    bg_=static_cast<Sprite*>(GetChild(String("bg")));
    ASSERT_CPP(bg_!=nullptr, " can not get bg");
    text_=static_cast<Text*>(GetChild(String("bg")));
    ASSERT_CPP(text_!=nullptr, " can not get text");
    SetText();
}
}

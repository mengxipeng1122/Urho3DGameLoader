

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

#include "Gamelist.hpp"
#include "../utils/log.hpp"
#include "../utils/string.hpp"

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

//    URHO3D_ATTRIBUTE("Tab Gap", int , tabGap_, 40, AM_FILE);
//    URHO3D_ATTRIBUTE("Select Color", Color, selectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
//    URHO3D_ATTRIBUTE("UnSelect Color", Color, unselectColor_, Color::TRANSPARENT_BLACK, AM_FILE);
}

Gamelist::Gamelist(Context *context)
    : UIElement(context)
{
}

bool Gamelist::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    bool success = UIElement::LoadXML(source, styleFile);
    ASSERT_CPP(success, "load XML failed ");


    Update();

    return success;
}

void Gamelist::Update()
{

}

bool Gamelist::HandleKeyDown( StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;
    return false;
}

}

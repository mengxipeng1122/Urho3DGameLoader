

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
#pragma once
#include <Urho3D/UI/Window.h>

#include "../utils/log.hpp"
#include "../InputSystem.hpp"

namespace Urho3D
{
class Text;
class BorderImage;
class CheckBox;
}

using namespace Urho3D;
namespace Urho3D
{

/// Text entry into a LineEdit. The text can be modified in the event data.
URHO3D_EVENT(E_TABCHANGED, TabChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_INDEX,   Index);                // String [in/out]
}



//=============================================================================
//=============================================================================
class TabSelector : public UIElement
{
    URHO3D_OBJECT(TabSelector, UIElement);
public:
    static void RegisterObject(Context* context);

    explicit TabSelector(Context *context);
    virtual ~TabSelector()override=default;

    void Update();

    void SetFocusing(bool b) { focusing_ = b; }
    bool IsFocusing() const { return focusing_; }

    bool HandleKeyDown(InputKey key);

protected:
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void Create(Context* context);
    void Quit();


    int             tabGap_{40};
    Color           selectColor_{0,0,0,1};
    Color           unselectColor_{1,1,1,1};

    int             index_{0};
    bool            focusing_{false}; 
    Vector2         cursorBasePosition{0,0};
    WeakPtr<Sprite> unselectCursor_;
    WeakPtr<Sprite> selectCursor_;
    Vector<WeakPtr<Text>>   tabs_;


private:
    bool LoadXML(const XMLElement& source, XMLFile* styleFile) override;

protected:
};
}



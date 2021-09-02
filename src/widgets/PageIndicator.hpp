
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

namespace Urho3D
{
class Text;
class BorderImage;
class CheckBox;
}

using namespace Urho3D;
namespace Urho3D
{
//=============================================================================
//=============================================================================
class PageIndicator : public UIElement
{
    URHO3D_OBJECT(PageIndicator, UIElement);
public:
    static void RegisterObject(Context* context);

    explicit PageIndicator(Context *context);
    virtual ~PageIndicator()override=default;

    void SetPage(int c, int t ) noexcept { curPageNo_ = c ; totalPageNo_ = t; SetText();  }

    void Update();

protected:
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void Quit();

    int curPageNo_{1};
    int totalPageNo_{1000};

    void SetText();

private:
    bool LoadXML(const XMLElement& source, XMLFile* styleFile) override;

protected:
    WeakPtr<Sprite>      bg_{nullptr};
    WeakPtr<Text>        text_{nullptr};
};
}



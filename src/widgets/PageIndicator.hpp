#pragma once

#include "../Global.h"

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



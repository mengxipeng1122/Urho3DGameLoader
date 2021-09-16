#pragma once

#include "Widget.hpp"
#include "../Global.h"

namespace Urho3D
{
//=============================================================================
//=============================================================================
class PageIndicator : public Widget
{
    URHO3D_OBJECT(PageIndicator, Widget);

public:
    static void RegisterObject(Context* context);

    explicit PageIndicator(Context *context);
    virtual ~PageIndicator()override=default;

    void SetPage(int c, int t ) noexcept { curPageNo_ = c ; totalPageNo_ = t; }

    DEF_TEXTURE_ATTR_SETTER_GETTER( Background, background)
    DEF_FONT_ATTR_SETTER_GETTER( Text, text)

protected:
//    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void Quit();

    int curPageNo_{1};
    int totalPageNo_{1000};

    String                              backgroundTexture_;

    Color                               textColor_{1,1,1,1};
    String                              textFont_;
    float                               textFontSize_{DEFAULT_FONT_SIZE};
    Vector2                             textPosition_{10,0};


    // void SetText();
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

private:
//    bool LoadXML(const XMLElement& source, XMLFile* styleFile) override;

protected:
//    WeakPtr<Sprite>      bg_{nullptr};
//    WeakPtr<Text>        text_{nullptr};
};
}



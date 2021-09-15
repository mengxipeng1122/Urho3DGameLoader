

#pragma once
#include "Widget.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{



//=============================================================================
//=============================================================================
class SearchEdit : public Widget
{
    URHO3D_OBJECT(SearchEdit, Widget);
public:
    static void RegisterObject(Context* context);

    explicit SearchEdit(Context *context);

    bool HandleKeyDown(InputKey key, int idx)override {return false;}

public:
    void Update();

    DEF_TEXTURE_ATTR_SETTER_GETTER( Background, background)

    DEF_FONT_ATTR_SETTER_GETTER( Text, text)

    void SetTexts(const String& key, int count) { key_=key; count_ = count; Update(); }

    /// Return UI rendering batches.
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

protected:

    String                              backgroundTexture_;
    Color                               textColor_{1,1,1,1};
    String                              textFont_;
    float                               textFontSize_{DEFAULT_FONT_SIZE};

    Vector2                             keyBasePosition_{10,0};
    int                                 keyStringGap_{15};
    Vector2                             countBasePosition_{10,0};

    String                              key_{""};
    int                                 count_{0};

private:
    void ApplyAttributes() override;


};

}



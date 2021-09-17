
//
#pragma once
#include "Widget.hpp"
#include "../Global.h"
#include "../utils/log.hpp"

namespace Urho3D
{

/// Text entry into a LineEdit. The text can be modified in the event data.

extern const char* UI_CATEGORY;

//=============================================================================
//=============================================================================
class MenuBar : public Widget
{
    URHO3D_OBJECT(MenuBar, Widget);

public:
    static void RegisterObject(Context* context);

    explicit MenuBar(Context *context);
    virtual ~MenuBar()override=default;


protected:
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
    bool HandleKeyDown(InputKey key, int idx) override;
    void Start() override;


public:
    void SetTextsAttr(const VariantVector& value) {
        texts_.Clear();
        if (!value.Size()) return ;
        for (VariantVector::ConstIterator i = value.Begin(); i != value.End(); ++i)
        {
            auto text = i->GetString();
            texts_.Push(text);
        }
    }
    VariantVector GetTextsAttr() const { VariantVector value; for (auto& text : texts_) { value.Push(text); } return value;  }

    DEF_TEXTURE_ATTR_SETTER_GETTER(Background, background)
    DEF_TEXTURE_ATTR_SETTER_GETTER(SelectCursor, selectCursor)
    DEF_TEXTURE_ATTR_SETTER_GETTER(UnselectCursor, unselectCursor)
    DEF_FONT_ATTR_SETTER_GETTER(Text, text)

    int GetIndex() const noexcept { return index_; }

protected:
    Color                   selectColor_{0,0,0,1};
    Color                   unselectColor_{1,1,1,1};
    String                  backgroundTexture_;
    Vector<String>          texts_;
    Vector<String>          displayTexts_;
    String                  selectCursorTexture_;
    String                  unselectCursorTexture_;
    String                  textFont_;
    float                   textFontSize_{DEFAULT_FONT_SIZE};
    bool                    textAutoLocalizable_{false};
    Vector2                 cursorBasePosition_{0,0};

    int                     index_{0};




};

}



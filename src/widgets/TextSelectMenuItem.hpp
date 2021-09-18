

#pragma once
#include "NormalMenuItem.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{



//=============================================================================
//=============================================================================
class TextSelectMenuItem : public NormalMenuItem
{
    URHO3D_OBJECT(TextSelectMenuItem, NormalMenuItem);
public:
    static void RegisterObject(Context* context);

    explicit TextSelectMenuItem(Context *context);

    DEF_TEXTURE_ATTR_SETTER_GETTER(UnselectLeftArrow, unselectLeftArrow)
    DEF_TEXTURE_ATTR_SETTER_GETTER(SelectLeftArrow, selectLeftArrow)
    DEF_TEXTURE_ATTR_SETTER_GETTER(UnselectRightArrow, unselectRightArrow)
    DEF_TEXTURE_ATTR_SETTER_GETTER(SelectRightArrow, selectRightArrow)

public:
    void SetOptionsAttr(const VariantVector& value) {
        options_.Clear();
        if (!value.Size()) return ;
        for (VariantVector::ConstIterator i = value.Begin(); i != value.End(); ++i) {
            auto option = i->GetString();
            options_.Push(option);
        }
    }
    VariantVector GetOptionsAttr() const { 
        VariantVector value; for (auto& option : options_) { value.Push(option); } return value;  
    }

    int getOptionIndex() const noexcept { return optionsIndex_; }

protected:
    Vector<String>          options_;
    int                     optionsIndex_{0};
    Vector2                 optionPosition_;
    String                  unselectLeftArrowTexture_;
    String                  selectLeftArrowTexture_;
    Vector2                 leftArrowPosition_;
    String                  unselectRightArrowTexture_;
    String                  selectRightArrowTexture_;
    Vector2                 rightArrowPosition_;

    bool HandleKeyDown(InputKey key, int idx)override;
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

private:

};

}





#pragma once
#include "NormalMenuItem.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{



//=============================================================================
//=============================================================================
class SelectMenuItem : public NormalMenuItem
{
    URHO3D_OBJECT(SelectMenuItem, NormalMenuItem);
public:
    static void RegisterObject(Context* context);

    explicit SelectMenuItem(Context *context);

    DEF_TEXTURE_ATTR_SETTER_GETTER(UnselectLeftArrow, unselectLeftArrow)
    DEF_TEXTURE_ATTR_SETTER_GETTER(SelectLeftArrow, selectLeftArrow)
    DEF_TEXTURE_ATTR_SETTER_GETTER(UnselectRightArrow, unselectRightArrow)
    DEF_TEXTURE_ATTR_SETTER_GETTER(SelectRightArrow, selectRightArrow)

public:
    void SetOptionsAttr(const VariantVector& value) {
        options_.Clear();
        if (!value.Size()) return ;
        for (VariantVector::ConstIterator i = value.Begin(); i != value.End(); ++i) {
            auto option = GetOptionFromVariantVectorItem(i);
            options_.Push(option);
        }
    }

    VariantVector GetOptionsAttr() const { 
        VariantVector value; 
        for (auto& option : options_) { 
            auto var = SetOptionToVariantVectorItem(option);
            value.Push(var);
        } 
        return value;  
    }

    int getOptionIndex() const noexcept { return optionsIndex_; }

protected:
    virtual String   GetOptionFromVariantVectorItem(VariantVector::ConstIterator& i) {ASSERT_CPP(false, "never call this function ");return String::EMPTY; }
    virtual Variant  SetOptionToVariantVectorItem(const String&) const { ASSERT_CPP(false, "never call this function ");return Variant::EMPTY;}
    virtual void     GetBatchesForOption(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor){ASSERT_CPP(false, "never call this function ");}
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



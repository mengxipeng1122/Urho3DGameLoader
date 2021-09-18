

#pragma once
#include "SelectMenuItem.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{



//=============================================================================
//=============================================================================
class TextSelectMenuItem : public SelectMenuItem
{
    URHO3D_OBJECT(TextSelectMenuItem, SelectMenuItem);
public:
    static void RegisterObject(Context* context);

    explicit TextSelectMenuItem(Context *context);

protected:
    String   GetOptionFromVariantVectorItem(VariantVector::ConstIterator& i) override
    {
        return i->GetString();
    }
    Variant  SetOptionToVariantVectorItem(const String& option) const override
    {
        return option;
    }
    void GetBatchesForOption(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

};

}



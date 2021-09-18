

#pragma once
#include "SelectMenuItem.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{



//=============================================================================
//=============================================================================
class ImageSelectMenuItem : public SelectMenuItem
{
    URHO3D_OBJECT(ImageSelectMenuItem, SelectMenuItem);
public:
    static void RegisterObject(Context* context);

    explicit ImageSelectMenuItem(Context *context);

protected:
    String   GetOptionFromVariantVectorItem(VariantVector::ConstIterator& i) override
    {
        return i->GetResourceRef().name_;
    }
    Variant  SetOptionToVariantVectorItem(const String& option) const override
    {
        ResourceRef ref(Texture2D::GetTypeStatic(), option);
        return ref;
    }
    void GetBatchesForOption(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

};

}



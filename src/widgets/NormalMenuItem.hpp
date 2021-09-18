

#pragma once
#include "MenuItem.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{



//=============================================================================
//=============================================================================
class NormalMenuItem : public MenuItem
{
    URHO3D_OBJECT(NormalMenuItem, MenuItem);
public:
    static void RegisterObject(Context* context);

    explicit NormalMenuItem(Context *context);

public:
    DEF_TEXTURE_ATTR_SETTER_GETTER(SelectBackground, selectBackground)
    DEF_TEXTURE_ATTR_SETTER_GETTER(UnselectBackground, unselectBackground)
    DEF_FONT_ATTR_SETTER_GETTER(Text, text)

protected:
    void ApplyAttributes() override;
    bool HandleKeyDown(InputKey key, int idx) override;
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)override;
    String                  selectBackgroundTexture_;
    String                  unselectBackgroundTexture_;
    String                  textFont_;
    String                  text_;
    Color                   selectColor_;
    Color                   unselectColor_;
    float                   textFontSize_{DEFAULT_FONT_SIZE};
    bool                    textAutoLocalizable_{false};
    Vector2                 textBasePosition_;

private:

};

}



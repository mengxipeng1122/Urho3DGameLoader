
#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "TextSelectMenuItem.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
//=============================================================================
void TextSelectMenuItem::RegisterObject(Context* context)
{
    context->RegisterFactory<TextSelectMenuItem>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(SelectMenuItem);
}

TextSelectMenuItem::TextSelectMenuItem(Context *context)
    : SelectMenuItem(context)
{
}

void TextSelectMenuItem::GetBatchesForOption(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    {
        auto font = CACHE->GetResource<Font>(textFont_);
        FontFace* face = font->GetFace(textFontSize_);
        ASSERT_CPP(optionsIndex_>=0 && optionsIndex_<options_.Size(), "optionsIndex_ error", optionsIndex_, "/", options_.Size());
        const String& str = options_[optionsIndex_];
        const int stringLineLength = Widget::GetStringLineWidth(str, face);
        auto offsetx = optionPosition_.x_ - stringLineLength/2;
        auto offsety = optionPosition_.y_;
        Widget::AddStringBatch(
                batches
              , vertexData
              , currentScissor
              , str
              , face
              , IsSelected() ? selectColor_ : unselectColor_
              , offsetx
              , offsety
              );
    }
}



}

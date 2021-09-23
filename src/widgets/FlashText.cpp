
#include "../utils/log.hpp"
#include "../utils/string.hpp"

#include "FlashText.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

//=============================================================================
//=============================================================================
void FlashText::RegisterObject(Context* context)
{
    context->RegisterFactory<FlashText>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Widget);

    URHO3D_ATTRIBUTE("Text Color", Color, textColor_, Color::TRANSPARENT_BLACK, AM_FILE);
    URHO3D_ATTRIBUTE("Text", String, text_, String::EMPTY, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Text Font", GetTextFontAttr, SetTextFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Text Font Size", float, textFontSize_, DEFAULT_FONT_SIZE, AM_FILE);
    URHO3D_ATTRIBUTE("Text Update Period", float, textUpdatePeroid_, DEFAULT_TEXT_UPDATE_PEROID, AM_FILE);

}

FlashText::FlashText(Context *context)
    : Widget(context)
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(FlashText, HandleUpdate));
}

FlashText::~FlashText()
{
    UnsubscribeFromEvent(E_UPDATE);
}



void FlashText::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    if(IsSelected()) {
        if(show_) {
            auto font = CACHE->GetResource<Font>(textFont_);
            FontFace* face = font->GetFace(textFontSize_);
            const auto& position = GetPosition();
            Widget::AddStringBatch(batches, vertexData, currentScissor, text_, face, textColor_ , 0,0);
        }
    }
}

void FlashText::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    elapsedTime_ += (eventData[P_TIMESTEP].GetFloat()*1000.f);
    if(elapsedTime_ > textUpdatePeroid_)
    {
        elapsedTime_ = 0.f;
        show_ = !show_;
    }
}


}

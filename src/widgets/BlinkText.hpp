

#pragma once
#include "Widget.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{



//=============================================================================
//=============================================================================
class BlinkText : public Widget
{
    URHO3D_OBJECT(BlinkText, Widget);
public:
    static void RegisterObject(Context* context);

    explicit BlinkText(Context *context);
    virtual ~BlinkText();

public:
    void SetText(const String& text) { text_ = text; }

public:
    DEF_FONT_ATTR_SETTER_GETTER(Text, text)

protected:
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)override;
    String                  textFont_;
    String                  text_;
    Color                   textColor_;
    float                   textFontSize_{DEFAULT_FONT_SIZE};
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

private:
    float     elapsedTime_{0.f};
    static constexpr float DEFAULT_TEXT_UPDATE_PEROID=1000.f;
    float     textUpdatePeroid_{DEFAULT_TEXT_UPDATE_PEROID};
    bool      show_{true};
    

};

}



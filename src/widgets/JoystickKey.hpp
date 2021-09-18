
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
class JoystickKey : public Widget
{
    URHO3D_OBJECT(JoystickKey, Widget);

public:
    static void RegisterObject(Context* context);

    explicit JoystickKey(Context *context);
    virtual ~JoystickKey()override=default;

    void SetState(const bool state) {state_ = state; }

protected:
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

    bool state_{false};

public:

    DEF_TEXTURE_ATTR_SETTER_GETTER(Image, image)  

protected:
    String                  imageTexture_;
    float                   imageScale_{1.2};

};

}



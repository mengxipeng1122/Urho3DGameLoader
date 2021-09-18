
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
class JoystickDir : public Widget
{
    URHO3D_OBJECT(JoystickDir, Widget);

public:
    static void RegisterObject(Context* context);

    explicit JoystickDir(Context *context);
    virtual ~JoystickDir()override=default;

    enum class State
    {
        CENTER,
        UP, 
        UP_RIGHT,
        RIGHT,
        DOWN_RIGHT,
        DOWN,
        DOWN_LEFT,
        LEFT,
        UP_LEFT,
    };

    void SetState(const State& state) {state_ = state; }

protected:
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

    State state_{State::CENTER};

public:
    void SetImagesAttr(const VariantVector& value) {
        images_.Clear();
        if (!value.Size()) return ;
        for (VariantVector::ConstIterator i = value.Begin(); i != value.End(); ++i)
        {
            auto image =  i->GetResourceRef().name_;
            images_.Push(image);
        }
    }
    VariantVector GetImagesAttr() const { 
        VariantVector value; 
        for (auto& image : images_) { 
            ResourceRef ref(Texture2D::GetTypeStatic(), image);
            value.Push(ref);
        } 
        return value;  
    }


protected:
    Vector<String>          images_;



};

}



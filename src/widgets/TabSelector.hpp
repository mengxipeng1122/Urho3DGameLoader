//
#pragma once
#include "../Global.h"

#include "../utils/log.hpp"

namespace Urho3D
{

/// Text entry into a LineEdit. The text can be modified in the event data.
URHO3D_EVENT(E_TABCHANGED, TabChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_INDEX,   Index);                // String [in/out]
}



//=============================================================================
//=============================================================================
class TabSelector : public UIElement
{
    URHO3D_OBJECT(TabSelector, UIElement);
public:
    static void RegisterObject(Context* context);

    explicit TabSelector(Context *context);
    virtual ~TabSelector()override=default;

    void Update();

    bool HandleKeyDown(InputKey key);

protected:
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void CreateChildren();
    void Quit();


public:
    void SetBackgroundTextureAttr(const ResourceRef& value) { backgroundTexture_ = value.name_ ; }
    ResourceRef GetBackgroundTextureAttr() const { return ResourceRef(Texture2D::GetTypeStatic(), backgroundTexture_ ); }

    void SetTextsAttr(const VariantVector& value) {
        texts_.Clear();
        if (!value.Size()) return ;
         for (VariantVector::ConstIterator i = value.Begin(); i != value.End(); ++i)
         {
             auto text = i->GetString();
             texts_.Push(text);
         }
        }
    VariantVector GetTextsAttr() const { VariantVector value; for (auto& text : texts_) { value.Push(text); } return value;  }

    void SetSelectCursorTextureAttr(const ResourceRef& value) { selectCursorTexture_ = value.name_ ; }
    ResourceRef GetSelectCursorTextureAttr() const { return ResourceRef(Texture2D::GetTypeStatic(), selectCursorTexture_ ); }

    void SetUnselectCursorTextureAttr(const ResourceRef& value) { unselectCursorTexture_ = value.name_ ; }
    ResourceRef GetUnselectCursorTextureAttr() const { return ResourceRef(Texture2D::GetTypeStatic(), unselectCursorTexture_ ); }

    void SetTextFontAttr(const ResourceRef& value) { textFont_ = value.name_ ; }
    ResourceRef GetTextFontAttr() const { return ResourceRef(Font::GetTypeStatic(), textFont_ ); }

    int GetIndex() const noexcept { return index_; }

protected:
    Color                   selectColor_{0,0,0,1};
    Color                   unselectColor_{1,1,1,1};
    String                  backgroundTexture_;
    Vector<String>          texts_;
    String                  selectCursorTexture_;
    String                  unselectCursorTexture_;
    String                  textFont_;
    float                   textFontSize_{DEFAULT_FONT_SIZE};
    bool                    textAutoLocalization_{false};
    Vector2                 cursorBasePosition_{0,0};

    int                     index_{0};
    WeakPtr<Sprite>         cursor_;
    Vector<WeakPtr<Text>>   tabs_;


private:
    bool LoadXML(const XMLElement& source, XMLFile* styleFile) override;

protected:
};
}



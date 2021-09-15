

#pragma once
#include "Widget.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{



//=============================================================================
//=============================================================================
class SearchEdit : public UIElement
{
    URHO3D_OBJECT(SearchEdit, UIElement);
public:
    static void RegisterObject(Context* context);

    explicit SearchEdit(Context *context);

public:
    void Update();

    DEF_TEXTURE_ATTR_SETTER_GETTER( Background, background)

    DEF_FONT_ATTR_SETTER_GETTER( Text, text)

    void SetTexts(const String& key, int count) { key_=key; count_ = count; Update(); }

protected:

    void CreateChildren();
    String                              backgroundTexture_;
    Color                               textColor_{1,1,1,1};
    String                              textFont_;
    float                               textFontSize_{DEFAULT_FONT_SIZE};

    Vector2                             keyBasePosition_{10,0};
    Vector2                             countBasePosition_{10,0};

    String                              key_{""};
    int                                 count_{0};

private:
    bool LoadXML(const XMLElement& source, XMLFile* styleFile) override;


};

}



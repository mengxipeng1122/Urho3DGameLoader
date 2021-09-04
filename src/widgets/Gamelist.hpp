
#pragma once
#include "../Global.h"

#include "../utils/log.hpp"
#include "../InputSystem.hpp"

namespace Urho3D
{

// /// Text entry into a LineEdit. The text can be modified in the event data.
// URHO3D_EVENT(E_TABCHANGED, TabChanged)
// {
//     URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
//     URHO3D_PARAM(P_INDEX,   Index);                // String [in/out]
// }



//=============================================================================
//=============================================================================
class Gamelist : public UIElement
{
    URHO3D_OBJECT(Gamelist, UIElement);
public:
    static void RegisterObject(Context* context);

    explicit Gamelist(Context *context);
    virtual ~Gamelist()override=default;


    bool HandleKeyDown(InputKey key);

public:
    struct Item
    {
        String thumbnailPath_;
        String name_;
        bool   marked;
    };
    void addItem(const Item& item);
    void Update();

#define DEF_TEXTURE_ATTR_SETTER_GETTER( n0, n1 ) \
    void Set ## n0 ## TextureAttr(const ResourceRef& value) { n1 ## Texture_ = value.name_ ; }  \
    ResourceRef Get ## n0 ## TextureAttr() const { return ResourceRef(Texture2D::GetTypeStatic(), n1 ## Texture_ ); } \

    DEF_TEXTURE_ATTR_SETTER_GETTER( ListMask, listMask)
    DEF_TEXTURE_ATTR_SETTER_GETTER( ListMaskSelect,  listMaskSelect)
    DEF_TEXTURE_ATTR_SETTER_GETTER( ListIconDefault, listIconDefault)
    DEF_TEXTURE_ATTR_SETTER_GETTER( ItemBackground,  itemBackground)
    DEF_TEXTURE_ATTR_SETTER_GETTER( ItemBackgroundSelect,  itemBackgroundSelect)

    void SetTextFontAttr(const ResourceRef& value) { textFont_ = value.name_ ; }
    ResourceRef GetTextFontAttr() const { return ResourceRef(Font::GetTypeStatic(), textFont_ ); }

protected:

    int                                 pageItems_{10};
    int                                 itemGap_{3};
    String                              listMaskTexture_;
    String                              listMaskSelectTexture_;
    String                              listIconDefaultTexture_;
    String                              itemBackgroundTexture_;
    String                              itemBackgroundSelectTexture_;
    Vector2                             itemBasePosition_{13,0};
    IntVector2                          listIconSize_{0,0};
    Color                               selectColor_{0,0,0,1};
    Color                               unselectColor_{1,1,1,1};
    String                              textFont_;
    float                               textFontSize_{DEFAULT_FONT_SIZE};

    std::vector<std::unique_ptr<Item>>  games_;
    int                                 index_{0};
    Vector<WeakPtr<UIElement>>          UIItems_; // this vector store all UI items for display one game 

    void CreateChildren();


private:
    bool LoadXML(const XMLElement& source, XMLFile* styleFile) override;

};

}



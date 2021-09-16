
#pragma once
#include "Widget.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{



//=============================================================================
//=============================================================================
class Gamelist : public Widget
{
    URHO3D_OBJECT(Gamelist, UIElement);
public:
    static void RegisterObject(Context* context);

    explicit Gamelist(Context *context);
    virtual ~Gamelist()override=default;


    bool HandleKeyDown(InputKey key, int idx) override;


public:
    struct Item
    {
        String iconPath_;
        String name_;
        bool   marked{false};
    };
private :
    std::vector<std::unique_ptr<Item>>  games_;
public:
    void ClearItems(){ games_.clear(); }
    void AddItem(const Item& item);
    //void Update()override;
    int  GetGameItemsCount() const noexcept { return games_.size() ; }

    DEF_TEXTURE_ATTR_SETTER_GETTER( ListMask, listMask)
    DEF_TEXTURE_ATTR_SETTER_GETTER( ListMaskSelect,  listMaskSelect)
    DEF_TEXTURE_ATTR_SETTER_GETTER( ListIconDefault, listIconDefault)
    DEF_TEXTURE_ATTR_SETTER_GETTER( ItemBackground,  itemBackground)
    DEF_TEXTURE_ATTR_SETTER_GETTER( ItemBackgroundSelect,  itemBackgroundSelect)

    DEF_FONT_ATTR_SETTER_GETTER( Text, text)

    int GetIndex() const noexcept { return firstIndex_+index_; }
    void ResetIndex() { firstIndex_=0; index_=0;}

    int GetPageItems() const noexcept { return pageItems_; }

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

    int                                 firstIndex_{0};
    int                                 index_{0};
//    Vector<WeakPtr<UIElement>>          UIItems_; // this vector store all UI items for display one game 

//    void CreateChildren();


private:
//    bool LoadXML(const XMLElement& source, XMLFile* styleFile) override;

    int goNextPage();
    int goPreviousPage();
    int goNextItem();
    int goPreviousItem();

};

}



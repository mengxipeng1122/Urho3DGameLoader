
#pragma once
#include "Widget.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{


enum class  WifiSignalStrength
{
    _0,
    _1,
    _2,
    _3,
    
};

//=============================================================================
//=============================================================================
class WifiList : public Widget
{
    URHO3D_OBJECT(WifiList, UIElement);
public:
    static void RegisterObject(Context* context);

    explicit WifiList(Context *context);
    virtual ~WifiList()override=default;

public:
    struct Item
    {
        String              SSID_;
        WifiSignalStrength  signalStrength_;
        bool                needPassword_;
    };

private :
    Vector<Item>  aps_;

public:
    void ClearItems(){ aps_.Clear(); }
    void AddItem(const Item& item);
    int  GetItemsCount() const noexcept { return aps_.Size() ; }

    DEF_TEXTURE_ATTR_SETTER_GETTER( Background,             background          )
    DEF_TEXTURE_ATTR_SETTER_GETTER( SelectBackground,       selectBackground    )
    DEF_TEXTURE_ATTR_SETTER_GETTER( WifiSignalStrength0,    wifiSignalStrength0 )
    DEF_TEXTURE_ATTR_SETTER_GETTER( WifiSignalStrength1,    wifiSignalStrength1 )
    DEF_TEXTURE_ATTR_SETTER_GETTER( WifiSignalStrength2,    wifiSignalStrength2 )
    DEF_TEXTURE_ATTR_SETTER_GETTER( WifiSignalStrength3,    wifiSignalStrength3 )
    DEF_TEXTURE_ATTR_SETTER_GETTER( WifiPassword,           wifiPassword        )

    DEF_FONT_ATTR_SETTER_GETTER( Text, text)

    int GetIndex() const noexcept { return firstIndex_+index_; }
    void ResetIndex() { firstIndex_=0; index_=0;}
    void UpdateDrawItems();

    int GetPageItems() const noexcept { return pageItems_; }
    bool HandleKeyDown(InputKey key, int idx) override;

protected:

    int                                 pageItems_{10};
    int                                 itemGap_{3};
    String                              backgroundTexture_;
    String                              selectBackgroundTexture_;
    String                              wifiSignalStrength0Texture_;
    String                              wifiSignalStrength1Texture_;
    String                              wifiSignalStrength2Texture_;
    String                              wifiSignalStrength3Texture_;
    String                              wifiPasswordTexture_;
    Color                               selectColor_{0,0,0,1};
    Color                               unselectColor_{1,1,1,1};
    String                              textFont_;
    float                               textFontSize_{DEFAULT_FONT_SIZE};

    int                                 firstIndex_{0};
    int                                 index_{0};

private:
//    bool LoadXML(const XMLElement& source, XMLFile* styleFile) override;
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
    //void Start() override;

    int goNextPage();
    int goPreviousPage();
    int goNextItem();
    int goPreviousItem();

};

}



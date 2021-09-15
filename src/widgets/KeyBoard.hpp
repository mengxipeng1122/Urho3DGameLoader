

#pragma once
#include "Widget.hpp"
#include "../utils/log.hpp"

namespace Urho3D
{



//=============================================================================
//=============================================================================
class KeyBoard : public Widget
{
    URHO3D_OBJECT(KeyBoard, UIElement);
public:
    static void RegisterObject(Context* context);

    explicit KeyBoard(Context *context);

    bool HandleKeyDown(InputKey key) override;

public:
    void Update();

    DEF_TEXTURE_ATTR_SETTER_GETTER( KeyBackground, keyBackground)
    DEF_TEXTURE_ATTR_SETTER_GETTER( KeySelect,     keySelect)      
    DEF_TEXTURE_ATTR_SETTER_GETTER( KeyClear,      keyClear)       
    DEF_TEXTURE_ATTR_SETTER_GETTER( KeyDel,        keyDel)       
    DEF_TEXTURE_ATTR_SETTER_GETTER( KeyShift,      keyShift)     
    DEF_TEXTURE_ATTR_SETTER_GETTER( KeySpace,      keySpace)     

    DEF_FONT_ATTR_SETTER_GETTER( Text, text)

    /// Return UI rendering batches.
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

protected:

    void CreateChildren();
    String                              keyBackgroundTexture_;
    String                              keySelectTexture_;
    String                              keyClearTexture_;
    String                              keyDelTexture_;
    String                              keyShiftTexture_;
    String                              keySpaceTexture_;
    Color                               textUnselectColor_{0,0,0,1};
    Color                               textSelectColor_{1,1,1,1};
    String                              textFont_;
    float                               textFontSize_{DEFAULT_FONT_SIZE};

    Vector2                             keyGap_{2,2};

    String                              str_{""};

private:
    bool LoadXML(const XMLElement& source, XMLFile* styleFile) override;
    static constexpr const int cols_ = 10;
    static constexpr const int rows_ = 4;
    static constexpr const char CHAR_CLEAR = '\x0';
    static constexpr const char CHAR_DEL   = '\x8';
    static constexpr const char CHAR_SPACE = ' ';
    static constexpr std::array<char, cols_*rows_> chars_ = {
        '1', '2', '3', '4', '5',        '6', '7', '8', '9', '0',
        'Q', 'W', 'E', 'R', 'T',        'Y', 'U', 'I', 'O', 'P',
        'A', 'S', 'D', 'F', 'G',        'H', 'J', 'K', 'L', CHAR_DEL,
        'Z', 'X', 'C', 'V', CHAR_SPACE, 'B', 'N', 'M', '-', CHAR_SPACE,
        };


};

}



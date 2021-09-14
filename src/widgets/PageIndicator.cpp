
#include "PageIndicator.hpp"
#include "../utils/log.hpp"
#include "../utils/string.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

#include <Urho3D/DebugNew.h>
//=============================================================================
//=============================================================================
void PageIndicator::RegisterObject(Context* context)
{
    context->RegisterFactory<PageIndicator>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);
}

PageIndicator::PageIndicator(Context *context)
    : UIElement(context)
{
}


void PageIndicator::Quit()
{
    UnsubscribeFromEvent(E_UPDATE);
}

bool PageIndicator::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    bool success = UIElement::LoadXML(source, styleFile);
    ASSERT_CPP(success, "load XML failed ");
    // get bg
    bg_   = static_cast<Sprite*>(GetChild(String("bg")));
    ASSERT_CPP(bg_!=nullptr, " can not found bg ");
    text_ = static_cast<Text*>(GetChild(String("text")));
    ASSERT_CPP(text_!=nullptr, " can not found text ");
    SetText();

    return success;
}

void PageIndicator::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

}

void PageIndicator::SetText()
{
    ASSERT_CPP(text_!=nullptr, " can not get text");
    LOG_INFOS_CPP(" go here ");
    std::string s = ConstructStringWithFormat("%03d/%04d",curPageNo_, totalPageNo_);
    text_->SetText(ToString(s.c_str()));
}


void PageIndicator::Update()
{
    bg_=static_cast<Sprite*>(GetChild(String("bg")));
    ASSERT_CPP(bg_!=nullptr, " can not get bg");
    text_=static_cast<Text*>(GetChild(String("bg")));
    ASSERT_CPP(text_!=nullptr, " can not get text");
    SetText();
}
}

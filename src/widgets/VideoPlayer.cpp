
#include "VideoPlayer.hpp"
#include "../utils/log.hpp"
#include "../components/VideoPlayerComponent.hpp"
#include "../utils/string.hpp"

namespace Urho3D
{
extern const char* UI_CATEGORY;

#include <Urho3D/DebugNew.h>
//=============================================================================
//=============================================================================
void VideoPlayer::RegisterObject(Context* context)
{
    context->RegisterFactory<VideoPlayer>(UI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(BorderImage);

}

VideoPlayer::VideoPlayer(Context *context)
    : BorderImage(context)
{
	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(VideoPlayer, HandleUpdate));
}


void VideoPlayer::Quit()
{
    UnsubscribeFromEvent(E_UPDATE);
}

bool VideoPlayer::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    bool success = UIElement::LoadXML(source, styleFile);
    ASSERT_CPP(success, "load XML failed ");

    LOG_INFOS_CPP(" go here");

    vp = new VideoPlayerComponent(context_);
    vp->OpenFileName("dinopb.avi");
    auto *m = CACHE->GetResource<Material>("Materials/TVmaterialGPUYUV.1.xml");
	vp->SetOutputMaterial(m);
    SetMaterial(m);


    return success;
}

void VideoPlayer::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    //LOG_INFOS_CPP(" go here");
    if(vp!=nullptr) vp->HandleUpdate(eventType, eventData);

}


}

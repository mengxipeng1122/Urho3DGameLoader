#pragma once


#include "../Global.h"
class VideoPlayerComponent;

namespace Urho3D
{
//=============================================================================
//=============================================================================
class VideoPlayer : public BorderImage
{
    URHO3D_OBJECT(VideoPlayer, BorderImage);
public:
    static void RegisterObject(Context* context);

    explicit VideoPlayer(Context *context);
    virtual ~VideoPlayer()override=default;
    void OpenFileName(const String& fn);
    void Close();

//    void Update();

protected:
	SharedPtr<VideoPlayerComponent> vp;
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void Quit();


private:
    bool LoadXML(const XMLElement& source, XMLFile* styleFile) override;

protected:
};
}



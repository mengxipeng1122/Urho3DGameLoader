
#pragma once
#include <Urho3D/Resource/XMLFile.h>

using namespace Urho3D;

class Settings: public Object
{
    URHO3D_OBJECT(Settings, Object);

    private:
        SharedPtr<XMLFile> xmlFile_{nullptr};
        String             lang_{"cn"};
        String             videoPath_{"movie/"};
        String             thumbnailPath_{"thumbnali/"};
    public:
        Settings(Context* Context, const char* xmlfileName);
        //////////////////////////////////////////////////    
        // getters/setters
        const String& getLanguage()         const noexcept {return lang_;           };
        const String& getVideoPath()        const noexcept {return videoPath_;      };
        const String& getThumbnaliPath()    const noexcept {return thumbnailPath_;  };

};


#pragma once
#include <Urho3D/Resource/XMLFile.h>

using namespace Urho3D;

class Settings: public Object
{
    URHO3D_OBJECT(Settings, Object);

    private:
        SharedPtr<XMLFile> xmlFile_{nullptr};
        String             lang_{"cn"};
        String             videoPathFormat_{"movie/%s.avi"};
        String             thumbnailPathFormat_{"thumbnali/%s.png"};
        String             iconPathFormat_{"icon/%s.png"};
    public:
        Settings(Context* Context, const char* xmlfileName);
        //////////////////////////////////////////////////    
        // getters/setters
        const String& GetLanguage()             const noexcept {return lang_;               };
        const String& GetVideoPathFormat()      const noexcept {return videoPathFormat_;    };
        const String& GetThumbnailPathFormat()  const noexcept {return thumbnailPathFormat_;};
        const String& GetIconPathFormat()       const noexcept {return iconPathFormat_;     };

};

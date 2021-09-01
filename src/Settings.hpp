
#pragma once
#include <Urho3D/Resource/XMLFile.h>

using namespace Urho3D;

class Settings
{
    private:
        SharedPtr<XMLFile> xmlFile_{nullptr};
        String             lang_{"cn"};
    public:
        Settings(Context* Context, const char* xmlfileName);
        virtual ~Settings()=default;

        //////////////////////////////////////////////////    
        // getters/setters
        const String& getLanguage() const noexcept {return lang_; };

};

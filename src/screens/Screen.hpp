
#pragma once

#include <vector>
#include <string>
#include "../Global.h"


class Screen : public UIElement
{
    public:
        Screen(Context* context):UIElement(context){}
        virtual ~Screen()=default;
        virtual void Enter() ;
        virtual void Leave() ;
        // this function handle events
        void HandleInputKeyDown(StringHash eventType, VariantMap& eventData);
        void HandleInputKeyUp(StringHash eventType, VariantMap& eventData);
        virtual bool HandleKeyDown(InputKey key, int idx){return false;}
        virtual bool HandleKeyUp(InputKey key, int idx){ return false;}

    protected:
        void LoadScreen(const String& resPath)
        {
            auto* screen = UI_ROOT->CreateChild<UIElement>(String("Screen"));
            SharedPtr<File> file = CACHE->GetFile(resPath); 
            screen->LoadXML(*file);
        }
};



#pragma once

#include <vector>
#include <string>
#include "../Global.h"
#include "../utils/log.hpp"


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
        virtual bool HandleKeyDown(InputKey key, int idx);
        virtual bool HandleKeyUp(InputKey key, int idx){ return false;}

#ifdef _DEBUG
        constexpr static bool HAS_DEBUG = true;
        using DEBUG_UIELEMENT_TYPE=Text;
        constexpr static const char* DEBUG_UIELEMENT_NAME { "_debug"};
        Vector<WeakPtr<UIElement>> allUIElements_;
        int  currentDebugUIElementIdx_ {0};
#else
        constexpr static bool HAS_DEBUG = false;
#endif

    protected:
        void InitAllUIElements();
        void UpdataDebugElment() 
        {
            if(HAS_DEBUG) {
                auto debugUIElement = UI_ROOT->GetChildStaticCast<DEBUG_UIELEMENT_TYPE>(String(DEBUG_UIELEMENT_NAME));
                if(currentDebugUIElementIdx_<allUIElements_.Size()) {
                    auto currentDebugUIElement = allUIElements_[currentDebugUIElementIdx_];
                    debugUIElement->SetText(currentDebugUIElement->GetName());
                    debugUIElement->SetPosition(currentDebugUIElement->GetPosition());
                    debugUIElement->SetSize(currentDebugUIElement->GetSize());
                }
            }
        }
        void LoadScreen(const String& resPath)
        {
            auto* screen = UI_ROOT->CreateChild<UIElement>(String("Screen"));
            SharedPtr<File> file = CACHE->GetFile(resPath); 
            screen->LoadXML(*file);
        }
};


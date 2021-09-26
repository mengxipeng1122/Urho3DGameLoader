
#pragma once

#include "../Global.h"
#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "../widgets/JoystickDir.hpp"
#include "../widgets/JoystickKey.hpp"


class WifiScreen : public Screen
{
    public:
        WifiScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key, int idx) override;
        bool HandleKeyUp(InputKey key, int idx) override;
        static const char* GetName() {return "Wifi";}

    private:

        class ScanWifiThread: public Thread
        {
            public:
                ScanWifiThread(): Thread(){}
            private:
                void ThreadFunction()
                {
                    LOG_INFOS_CPP("scanWifiThread");
                    while(shouldRun_)
                    {
                        LOG_INFOS_CPP("scan wifi");
                        Time::Sleep(1000);
                    }
                    LOG_INFOS_CPP("scanWifiThread bye");
                }
        };

        ScanWifiThread scanWifiWorker_;
};

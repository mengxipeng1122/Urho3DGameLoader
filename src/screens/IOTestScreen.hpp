
#pragma once

#include "../Global.h"
#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "../widgets/JoystickDir.hpp"
#include "../widgets/JoystickKey.hpp"


class IOTestScreen : public Screen
{
    public:
        IOTestScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key, int idx) override;
        bool HandleKeyUp(InputKey key, int idx) override;
        static const char* GetName() {return "IOTest";}

    private:
        WeakPtr<JoystickDir> joystickDir1p_;
        WeakPtr<JoystickKey> joystickSelect1p_;
        WeakPtr<JoystickKey> joystickStart1p_;
        WeakPtr<JoystickKey> joystickA1p_;
        WeakPtr<JoystickKey> joystickB1p_;
        WeakPtr<JoystickKey> joystickC1p_;
        WeakPtr<JoystickKey> joystickD1p_;
        WeakPtr<JoystickKey> joystickE1p_;
        WeakPtr<JoystickKey> joystickF1p_;

        WeakPtr<JoystickDir> joystickDir2p_;
        WeakPtr<JoystickKey> joystickSelect2p_;
        WeakPtr<JoystickKey> joystickStart2p_;
        WeakPtr<JoystickKey> joystickA2p_;
        WeakPtr<JoystickKey> joystickB2p_;
        WeakPtr<JoystickKey> joystickC2p_;
        WeakPtr<JoystickKey> joystickD2p_;
        WeakPtr<JoystickKey> joystickE2p_;
        WeakPtr<JoystickKey> joystickF2p_;

        void UpdateWidget();  
        void UpdateJoystick(WeakPtr<JoystickDir>& widget, int idx);
};

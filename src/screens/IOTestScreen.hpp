
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
        Vector<bool> keysIsHolding_{
            false,  // UP       1p
            false,  // DOWN     1p
            false,  // LEFT     1p
            false,  // RIGHT    1p
            false,  // SELECT   1p
            false,  // START    1p
            false,  // A        1p
            false,  // B        1p
            false,  // C        1p
            false,  // D        1p
            false,  // E        1p
            false,  // F        1p
            false,  // UP       2p
            false,  // DOWN     2p
            false,  // LEFT     2p
            false,  // RIGHT    2p
            false,  // SELECT   2p
            false,  // START    2p
            false,  // A        2p
            false,  // B        2p
            false,  // C        2p
            false,  // D        2p
            false,  // E        2p
            false,  // F        2p
            };
};

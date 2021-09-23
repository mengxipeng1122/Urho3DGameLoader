
#pragma once

#include <set>
#include "../Global.h"
#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "../widgets/BlinkText.hpp"
#include "../widgets/NormalMenuItem.hpp"


class KeySettingScreen : public Screen
{
    public:
        KeySettingScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key, int idx) override;
        bool HandleKeyUp(InputKey key, int idx) override;
        static const char* GetName() {return "KeySetting";}

    private:

        WeakPtr<BlinkText>      keyTipText_;
        WeakPtr<NormalMenuItem> saveButton_;
        WeakPtr<NormalMenuItem> restoreDefaultButton_;

        enum class KeySettingState {
            PLAYER1_A,
            PLAYER1_B,
            PLAYER1_C,
            PLAYER1_D,
            PLAYER1_E,
            PLAYER1_F,

            PLAYER2_A,
            PLAYER2_B,
            PLAYER2_C,
            PLAYER2_D,
            PLAYER2_E,
            PLAYER2_F,
        };
        const char* GetKeyStateTip();
        KeySettingState keyState_{KeySettingState::PLAYER1_A};
        void AdvanceKeyState();

        enum class KeyButtonState {
            A,
            B,
            C,
            D,
            E,
            F,
            EMPTY,
        };
        std::array<WeakPtr<Sprite>,Machine::MAXIMUM_PLAYERS*Machine::MAXIMUM_KEYS>  buttons_;
        std::array<KeyButtonState,Machine::MAXIMUM_PLAYERS*Machine::MAXIMUM_KEYS>   buttonStates_;
        void UpdateAllButtonStateByKeyMap();
        void SetKeyMapByAllButtonsState();
        void UpdateAllButtons();

        static KeyButtonState ConvertInputKey2ButtonState(const InputKey& key);

        std::set<InputKey> allowInputKeys{
                InputKey::FIRE_A,
                InputKey::FIRE_B,
                InputKey::FIRE_C,
                InputKey::FIRE_D,
                InputKey::FIRE_E,
                InputKey::FIRE_F,
            };



};

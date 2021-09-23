
#include "KeySettingScreen.hpp"
#include "SettingsScreen.hpp"
#include "../widgets/TextSelectMenuItem.hpp"
#include "../widgets/ImageSelectMenuItem.hpp"

void KeySettingScreen::Enter()
{
    Screen::Enter();
    Screen::LoadScreen(ToString("screens/%s.xml", GetName()));
    Screen::InitAllUIElements();

    const auto* screen = UI_ROOT->GetChildStaticCast<UIElement>(String("Screen"));

    keyTipText_ = screen->GetChildStaticCast<BlinkText>(String("Key Tip"));
    ASSERT_CPP(keyTipText_!=nullptr, "can not found Key Tip ");
    keyTipText_->SetSelected(true);
    keyTipText_->SetText(String(GetKeyStateTip()));

    saveButton_ = screen->GetChildStaticCast<NormalMenuItem>(String("Save"));
    ASSERT_CPP(saveButton_!=nullptr, "can not found Save");
    saveButton_->SetSelected(false);

    restoreDefaultButton_ = screen->GetChildStaticCast<NormalMenuItem>(String("Restore Default"));
    ASSERT_CPP(restoreDefaultButton_!=nullptr, "can not found Restore Default ");
    restoreDefaultButton_->SetSelected(false);

    buttons_[Machine::MAXIMUM_KEYS*0+0] = screen->GetChildStaticCast<Sprite>(String("Player 1 A"));
    buttons_[Machine::MAXIMUM_KEYS*0+1] = screen->GetChildStaticCast<Sprite>(String("Player 1 B"));
    buttons_[Machine::MAXIMUM_KEYS*0+2] = screen->GetChildStaticCast<Sprite>(String("Player 1 C"));
    buttons_[Machine::MAXIMUM_KEYS*0+3] = screen->GetChildStaticCast<Sprite>(String("Player 1 D"));
    buttons_[Machine::MAXIMUM_KEYS*0+4] = screen->GetChildStaticCast<Sprite>(String("Player 1 E"));
    buttons_[Machine::MAXIMUM_KEYS*0+5] = screen->GetChildStaticCast<Sprite>(String("Player 1 F"));

    buttons_[Machine::MAXIMUM_KEYS*1+0] = screen->GetChildStaticCast<Sprite>(String("Player 2 A"));
    buttons_[Machine::MAXIMUM_KEYS*1+1] = screen->GetChildStaticCast<Sprite>(String("Player 2 B"));
    buttons_[Machine::MAXIMUM_KEYS*1+2] = screen->GetChildStaticCast<Sprite>(String("Player 2 C"));
    buttons_[Machine::MAXIMUM_KEYS*1+3] = screen->GetChildStaticCast<Sprite>(String("Player 2 D"));
    buttons_[Machine::MAXIMUM_KEYS*1+4] = screen->GetChildStaticCast<Sprite>(String("Player 2 E"));
    buttons_[Machine::MAXIMUM_KEYS*1+5] = screen->GetChildStaticCast<Sprite>(String("Player 2 F"));

    UpdateAllButtonStateByKeyMap();
    UpdateAllButtons();
    
}

void KeySettingScreen::Leave()
{
    Screen::Leave();
}

bool KeySettingScreen::HandleKeyDown(InputKey key, int idx)
{
    Screen::HandleKeyDown(key, idx);

    // switch select focus
    if(keyTipText_->IsSelected()) {
        switch(key) {
            case InputKey::DOWN: 
                keyTipText_->SetSelected(false);
                saveButton_->SetSelected(true);
                return true;
        }
    }
    else if(saveButton_->IsSelected()){
        switch(key) {
            case InputKey::RIGHT:
                saveButton_->SetSelected(false);
                restoreDefaultButton_->SetSelected(true);
                return true;
            case InputKey::UP:
                saveButton_->SetSelected(false);
                keyTipText_->SetSelected(true);
                return true;
            case InputKey::FIRE_A:
                // save and exit 
                SetKeyMapByAllButtonsState();                
                MACHINE->SetSetttingScreenIndex(1);
                ScreenManager::SetCurrentScreen(SettingsScreen::GetName(), context_);
                return true;
        }
    }
    else if(restoreDefaultButton_->IsSelected()){
        switch(key) {
            case InputKey::LEFT:
                restoreDefaultButton_->SetSelected(false);
                saveButton_->SetSelected(true);
                return true;
            case InputKey::UP:
                restoreDefaultButton_->SetSelected(false);
                keyTipText_->SetSelected(true);
                return true;
            case InputKey::FIRE_A:
                MACHINE->RestoreKeyMap();
                MACHINE->SetSetttingScreenIndex(1);
                ScreenManager::SetCurrentScreen(SettingsScreen::GetName(), context_);
                return true;
        }
    }

    if(keyTipText_->IsSelected()) {
        switch(keyState_) 
        {
            case KeySettingState::PLAYER1_A:
            case KeySettingState::PLAYER1_B:
            case KeySettingState::PLAYER1_C:
            case KeySettingState::PLAYER1_D:
            case KeySettingState::PLAYER1_E:
            case KeySettingState::PLAYER1_F:
                if(idx == 0) {
                    if(allowInputKeys.find(key)!=allowInputKeys.end()) {
                        if(keyState_ == KeySettingState::PLAYER1_F) {
                            allowInputKeys = {
                                    InputKey::FIRE_A,
                                    InputKey::FIRE_B,
                                    InputKey::FIRE_C,
                                    InputKey::FIRE_D,
                                    InputKey::FIRE_E,
                                    InputKey::FIRE_F,
                            };
                        }
                        else {
                            allowInputKeys.erase(key);
                        }
                        auto nIdx = static_cast<int>(keyState_) -  static_cast<int>(KeySettingState::PLAYER1_A);
                        buttonStates_[Machine::MAXIMUM_KEYS*0+nIdx] = ConvertInputKey2ButtonState(key);
                        if(keyState_ == KeySettingState::PLAYER1_A) {
                            for(auto t = 1; t< Machine::MAXIMUM_KEYS ; t++) {
                                buttonStates_[Machine::MAXIMUM_KEYS*0+t] = KeyButtonState::EMPTY;
                            }
                        }
                        UpdateAllButtons();
                        AdvanceKeyState();
                        keyTipText_->SetText(String(GetKeyStateTip()));
                        return true;
                    }
                }
                break;

            case KeySettingState::PLAYER2_A:
            case KeySettingState::PLAYER2_B:
            case KeySettingState::PLAYER2_C:
            case KeySettingState::PLAYER2_D:
            case KeySettingState::PLAYER2_E:
            case KeySettingState::PLAYER2_F:
                if(idx == 1) {
                    if(allowInputKeys.find(key)!=allowInputKeys.end()) {
                        if(keyState_ == KeySettingState::PLAYER2_F) {
                            allowInputKeys = {
                                    InputKey::FIRE_A,
                                    InputKey::FIRE_B,
                                    InputKey::FIRE_C,
                                    InputKey::FIRE_D,
                                    InputKey::FIRE_E,
                                    InputKey::FIRE_F,
                            };
                        }
                        else {
                            allowInputKeys.erase(key);
                        }
                        auto nIdx = static_cast<int>(keyState_) -  static_cast<int>(KeySettingState::PLAYER2_A);
                        auto aIdx = Machine::MAXIMUM_KEYS*1+nIdx;
                        auto newButtonState =  ConvertInputKey2ButtonState(key);
                        LOG_INFOS_CPP(" aIdx ", aIdx, static_cast<int>(newButtonState));
                        buttonStates_[aIdx] = newButtonState;
                        if(keyState_ == KeySettingState::PLAYER2_A) {
                            for(auto t = 1; t< Machine::MAXIMUM_KEYS ; t++) {
                                buttonStates_[Machine::MAXIMUM_KEYS*1+t] = KeyButtonState::EMPTY;
                            }
                        }
                        UpdateAllButtons();
                        if(keyState_ == KeySettingState::PLAYER2_F) {
                            keyTipText_->SetSelected(false);
                            saveButton_->SetSelected(true);
                        }
                        AdvanceKeyState();
                        keyTipText_->SetText(String(GetKeyStateTip()));
                        return true;
                    }
                }
                break;
        }
    }
    return false;
}

bool KeySettingScreen::HandleKeyUp(InputKey key, int idx)
{
    Screen::HandleKeyUp(key, idx);
    return false;
}

const char* KeySettingScreen::GetKeyStateTip()
{
    switch(keyState_)
    {
        case KeySettingState::PLAYER1_A: return "PRESS PLAYER 1 A";
        case KeySettingState::PLAYER1_B: return "PRESS PLAYER 1 B";
        case KeySettingState::PLAYER1_C: return "PRESS PLAYER 1 C";
        case KeySettingState::PLAYER1_D: return "PRESS PLAYER 1 D";
        case KeySettingState::PLAYER1_E: return "PRESS PLAYER 1 E";
        case KeySettingState::PLAYER1_F: return "PRESS PLAYER 1 F";
        case KeySettingState::PLAYER2_A: return "PRESS PLAYER 2 A";
        case KeySettingState::PLAYER2_B: return "PRESS PLAYER 2 B";
        case KeySettingState::PLAYER2_C: return "PRESS PLAYER 2 C";
        case KeySettingState::PLAYER2_D: return "PRESS PLAYER 2 D";
        case KeySettingState::PLAYER2_E: return "PRESS PLAYER 2 E";
        case KeySettingState::PLAYER2_F: return "PRESS PLAYER 2 F";
    }
    ASSERT_CPP("keyState_ is not correct ", static_cast<int>(keyState_));
    return nullptr;
}

KeySettingScreen::KeyButtonState KeySettingScreen::ConvertInputKey2ButtonState(const InputKey& key){
    switch( key)
    {
        case InputKey::FIRE_A: return KeyButtonState::A;
        case InputKey::FIRE_B: return KeyButtonState::B;
        case InputKey::FIRE_C: return KeyButtonState::C;
        case InputKey::FIRE_D: return KeyButtonState::D;
        case InputKey::FIRE_E: return KeyButtonState::E;
        case InputKey::FIRE_F: return KeyButtonState::F;
        default:
            return KeyButtonState::EMPTY;
    }
}

void KeySettingScreen::UpdateAllButtonStateByKeyMap()
{
    buttonStates_[Machine::MAXIMUM_KEYS*0+0] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(0, InputKey::FIRE_A));
    buttonStates_[Machine::MAXIMUM_KEYS*0+1] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(0, InputKey::FIRE_B));
    buttonStates_[Machine::MAXIMUM_KEYS*0+2] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(0, InputKey::FIRE_C));
    buttonStates_[Machine::MAXIMUM_KEYS*0+3] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(0, InputKey::FIRE_E));
    buttonStates_[Machine::MAXIMUM_KEYS*0+4] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(0, InputKey::FIRE_D));
    buttonStates_[Machine::MAXIMUM_KEYS*0+5] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(0, InputKey::FIRE_F));

    buttonStates_[Machine::MAXIMUM_KEYS*1+0] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(1, InputKey::FIRE_A));
    buttonStates_[Machine::MAXIMUM_KEYS*1+1] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(1, InputKey::FIRE_B));
    buttonStates_[Machine::MAXIMUM_KEYS*1+2] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(1, InputKey::FIRE_C));
    buttonStates_[Machine::MAXIMUM_KEYS*1+3] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(1, InputKey::FIRE_E));
    buttonStates_[Machine::MAXIMUM_KEYS*1+4] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(1, InputKey::FIRE_D));
    buttonStates_[Machine::MAXIMUM_KEYS*1+5] = ConvertInputKey2ButtonState(MACHINE->GetKeyMap(1, InputKey::FIRE_F));
}

void KeySettingScreen::UpdateAllButtons()
{
    auto getButtonTextureByState = [&](KeyButtonState state){
        switch( state) {
            case KeyButtonState::A:     return CACHE->GetResource<Texture2D>("res/pad1_a.png");
            case KeyButtonState::B:     return CACHE->GetResource<Texture2D>("res/pad1_b.png");
            case KeyButtonState::C:     return CACHE->GetResource<Texture2D>("res/pad1_c.png");
            case KeyButtonState::D:     return CACHE->GetResource<Texture2D>("res/pad1_d.png");
            case KeyButtonState::E:     return CACHE->GetResource<Texture2D>("res/pad1_e.png");
            case KeyButtonState::F:     return CACHE->GetResource<Texture2D>("res/pad1_f.png");
            case KeyButtonState::EMPTY: 
            default:
                return CACHE->GetResource<Texture2D>("res/pad1_null.png");
        }
    };

    for(auto idx=0; idx<buttons_.size();idx++) {
        buttons_[idx]->SetTexture(getButtonTextureByState(buttonStates_[idx]));
    }
}

void KeySettingScreen::AdvanceKeyState()
{
    switch(keyState_) 
    {
        case KeySettingState::PLAYER1_A:  { keyState_ = KeySettingState::PLAYER1_B; break; }
        case KeySettingState::PLAYER1_B:  { keyState_ = KeySettingState::PLAYER1_C; break; }
        case KeySettingState::PLAYER1_C:  { keyState_ = KeySettingState::PLAYER1_D; break; }
        case KeySettingState::PLAYER1_D:  { keyState_ = KeySettingState::PLAYER1_E; break; }
        case KeySettingState::PLAYER1_E:  { keyState_ = KeySettingState::PLAYER1_F; break; }
        case KeySettingState::PLAYER1_F:  { keyState_ = KeySettingState::PLAYER2_A; break; }
        case KeySettingState::PLAYER2_A:  { keyState_ = KeySettingState::PLAYER2_B; break; }
        case KeySettingState::PLAYER2_B:  { keyState_ = KeySettingState::PLAYER2_C; break; }
        case KeySettingState::PLAYER2_C:  { keyState_ = KeySettingState::PLAYER2_D; break; }
        case KeySettingState::PLAYER2_D:  { keyState_ = KeySettingState::PLAYER2_E; break; }
        case KeySettingState::PLAYER2_E:  { keyState_ = KeySettingState::PLAYER2_F; break; }
        case KeySettingState::PLAYER2_F:  { keyState_ = KeySettingState::PLAYER1_A; break; }
    }
}

void KeySettingScreen::SetKeyMapByAllButtonsState()
{
    auto convertKeyButtonStateToInputKey = [](const KeyButtonState& keyButton){
        switch( keyButton)
        {
            case KeyButtonState::A: return InputKey::FIRE_A;
            case KeyButtonState::B: return InputKey::FIRE_B;
            case KeyButtonState::C: return InputKey::FIRE_C;
            case KeyButtonState::D: return InputKey::FIRE_D;
            case KeyButtonState::E: return InputKey::FIRE_E;
            case KeyButtonState::F: return InputKey::FIRE_F;
            default:
                ASSERT_CPP("key button is not correct ", static_cast<int>(keyButton));
                return InputKey::FIRE_A;
        }
    };

    for(auto idx = 0;idx<Machine::MAXIMUM_PLAYERS;idx++) {
        for (auto key = 0;key<Machine::MAXIMUM_KEYS; key++){
            auto aidx = idx*Machine::MAXIMUM_KEYS + key;
            auto buttonKey = buttonStates_[aidx];
            auto mapKey = convertKeyButtonStateToInputKey(buttonKey);
            auto actKey = ConvertIndexToInputKey(key);
            MACHINE->SetKeyMap(mapKey, idx, actKey);
        }
    }
}

   

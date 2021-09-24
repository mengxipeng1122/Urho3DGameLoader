
#pragma once

#include "../Global.h"
#include "ScreenBuilder.hpp"
#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "../widgets/Gamelist.hpp"
#include "../widgets/JoystickKey.hpp"


class GameSettingScreen : public Screen
{
    public:
        GameSettingScreen(Context* context):Screen(context){}
        void Enter() override;
        void Leave() override;
        bool HandleKeyDown(InputKey key, int idx) override;
        bool HandleKeyUp(InputKey key, int idx) override;
        static const char* GetName() {return "GameSetting";}

    private:
        WeakPtr<Gamelist>       gamelist_{nullptr};        
        void HandleGamelistChanged(StringHash eventType, VariantMap& eventData);
        void SetGamelist();

        struct GameInfo {
            int       lifeIdx_;
            Vector<GameLife>   validLives_;
            GameLevel level_;
        };
        Vector<GameInfo> gameInfos_;

    public:
        int totalGames_{0};
        int totalPages_{0};

        void UpdateGameListValues();
        void UpdateGameIndexIndicator();
        void UpdatePageIndexIndicator();
        void UpdateLevelListTexts();

        WeakPtr<Text> pageIndicator_{nullptr};
        WeakPtr<Text> gameIndicator_{nullptr};

        WeakPtr<Text> lifeText_{nullptr};
        WeakPtr<Text> levelText_{nullptr};
        
};

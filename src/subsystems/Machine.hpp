
#pragma once

#include <set>
#include "../Global.h"
#include "InputSystem.hpp"

enum class GameLife {
        INVALID,
        _1, 
        _2, 
        _3, 
        _4, 
};

inline const char* GetGamelifeString(GameLife gameLife)
{
    switch(gameLife)
    {
        case GameLife::_1: return "1";
        case GameLife::_2: return "2";
        case GameLife::_3: return "3";
        case GameLife::_4: return "4";
        case GameLife::INVALID: 
        default:
        return "";
    }
}

enum class GameLevel {
        INVALID,
        _2, 
        _4, 
        _6, 
        _8, 
};

inline const char* GetGameLevelString(GameLevel gameLevel)
{
    switch(gameLevel)
    {
        case GameLevel::_2: return "2";
        case GameLevel::_4: return "4";
        case GameLevel::_6: return "6";
        case GameLevel::_8: return "8";
        case GameLevel::INVALID: 
        default:
        return "";
    }
}



class Machine: public Object
{
    URHO3D_OBJECT(Machine, Object);

public:
    Machine(Context* context);

    ////////////////////////////////////////////////////////////////////////////////
    // game list related
public:
    struct GameItem {
        String                  name_;
        String                  rom_;
        int                     lifeIdx_;
        Vector<GameLife>        validLives_;
        GameLevel               level_;
        
    };
    // use cb to handle all found gameitem; cb is function 
    void HandleAllGames(std::function<void(const GameItem& gameItem)> cb);
    void HandleRecentGames(std::function<void(const GameItem& gameItem)> cb);
    void HandleFavoriteGames(std::function<void(const GameItem& gameItem)> cb);
    void SearchLocalGames(const String& key, std::function<void(const GameItem& gameItem)> cb);
    void SearchStoreGames(const String& key, std::function<void(const GameItem& gameItem)> cb);

    ////////////////////////////////////////////////////////////////////////////////
    // runtime
public:
    int GetSetttingScreenIndex() const noexcept { return settingScreenIndex_; }
    void SetSetttingScreenIndex(int i) {settingScreenIndex_ = i;}
private:
    int settingScreenIndex_{0};

    ////////////////////////////////////////////////////////////////////////////////
    // key map 
public:
    void SetKeyMap(InputKey actKey, int idx,  InputKey mapKey);
    InputKey GetKeyMap(int idx,  InputKey mapKey);
    void RestoreKeyMap();
    static constexpr int MAXIMUM_PLAYERS =2; 
    static constexpr int MAXIMUM_KEYS    =6; 
private:
    // a--0 , b--1 c--2 .etc
    std::array<int, MAXIMUM_PLAYERS*MAXIMUM_KEYS> keyMap_{
            0, 1, 2, 3, 4, 5,
            0, 1, 2, 3, 4, 5,
        }; 


};



#pragma once

#include "../Global.h"

class Machine: public Object
{
    URHO3D_OBJECT(Machine, Object);

public:
    Machine(Context* context);

    struct GameItem
    {
        String name_;
        String rom_;
    };

    // use cb to handle all found gameitem; cb is function 
    void HandleAllGames(std::function<void(const GameItem& gameItem)> cb);
    void HandleRecentGames(std::function<void(const GameItem& gameItem)> cb);
    void HandleFavoriteGames(std::function<void(const GameItem& gameItem)> cb);
    void SearchLocalGames(const String& key, std::function<void(const GameItem& gameItem)> cb);
    void SearchStoreGames(const String& key, std::function<void(const GameItem& gameItem)> cb);

private:

};


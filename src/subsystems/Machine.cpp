#include "Machine.hpp"
#include "../utils/log.hpp"

Machine::Machine(Context* context)
    : Object(context)
{
}


void Machine::HandleAllGames(std::function<void(const GameItem& gameItem)> cb)
{
    // TODO:
    auto* jgamelist = CACHE->GetResource<JSONFile>("allGamelist.json");
    auto  gamelist = jgamelist->GetRoot().GetArray();
    for(auto& game : gamelist)
    {
        GameItem item;
        item.name_ = game.Get("name").GetString();
        item.rom_ = game.Get("rom").GetString();
        cb(item);
    }
}

void Machine::HandleRecentGames(std::function<void(const GameItem& gameItem)> cb)
{
    // TODO:
    auto* jgamelist = CACHE->GetResource<JSONFile>("recentGamelist.json");
    auto  gamelist = jgamelist->GetRoot().GetArray();
    for(auto& game : gamelist)
    {
        GameItem item;
        item.name_ = game.Get("name").GetString();
        item.rom_ = game.Get("rom").GetString();
        LOG_INFOS_CPP(item.name_, item.rom_);
        cb(item);
    }
}

void Machine::HandleFavoriteGames(std::function<void(const GameItem& gameItem)> cb)
{
    // TODO:
    auto* jgamelist = CACHE->GetResource<JSONFile>("favoriteGamelist.json");
    auto  gamelist = jgamelist->GetRoot().GetArray();
    for(auto& game : gamelist)
    {
        GameItem item;
        item.name_ = game.Get("name").GetString();
        item.rom_ = game.Get("rom").GetString();
        LOG_INFOS_CPP(item.name_, item.rom_);
        cb(item);
    }
}

void Machine::SearchLocalGames(const String& key, std::function<void(const GameItem& gameItem)> cb)
{
}

void Machine::SearchStoreGames(const String& key, std::function<void(const GameItem& gameItem)> cb)
{
}

void Machine::SetKeyMap(InputKey actKey, int idx, InputKey mapKey)
{
    ASSERT_CPP(idx>=0 && idx < MAXIMUM_PLAYERS, "idx not correct",idx );
    ASSERT_CPP(IsKey(actKey), "actKey is not key ", static_cast<int>(actKey));
    ASSERT_CPP(IsKey(mapKey), "mapKey is not key ", static_cast<int>(mapKey));
    auto nActKey = ConvertInputKeyToIndex(actKey);
    auto nMapKey = ConvertInputKeyToIndex(mapKey);
    keyMap_[nMapKey+MAXIMUM_KEYS*idx] =nActKey;
}

InputKey Machine::GetKeyMap(int idx,  InputKey mapKey)
{
    ASSERT_CPP(idx>=0 && idx < MAXIMUM_PLAYERS, "idx not correct",idx );
    ASSERT_CPP(IsKey(mapKey), "mapKey is not key ", static_cast<int>(mapKey));
    auto nMapKey = ConvertInputKeyToIndex(mapKey);
    auto nActKey = keyMap_[nMapKey+MAXIMUM_KEYS*idx];
    return ConvertIndexToInputKey(nActKey);

}

void Machine::RestoreKeyMap()
{
    for(auto t=0;t<MAXIMUM_PLAYERS; t++) 
    {
        for(auto k=0;k<MAXIMUM_KEYS; k++) 
        {
            keyMap_[k+MAXIMUM_KEYS*t] = t;
        }
    }

}

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
        LOG_INFOS_CPP(item.name_, item.rom_);
        cb(item);
    }
}

void Machine::HandleRecentGames(std::function<void(const GameItem& gameItem)> cb)
{
}

void Machine::HandleFavoriteGames(std::function<void(const GameItem& gameItem)> cb)
{
}

void Machine::SearchLocalGames(const String& key, std::function<void(const GameItem& gameItem)> cb)
{
}

void Machine::SearchStoreGames(const String& key, std::function<void(const GameItem& gameItem)> cb)
{
}

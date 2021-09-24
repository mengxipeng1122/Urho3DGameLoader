
#include "../utils/string.hpp"
#include "GameSettingScreen.hpp"
#include "SettingsScreen.hpp"
#include "../widgets/TextSelectMenuItem.hpp"
#include "../widgets/ImageSelectMenuItem.hpp"

void GameSettingScreen::Enter()
{
    Screen::Enter();
    Screen::LoadScreen(ToString("screens/%s.xml", GetName()));
    Screen::InitAllUIElements();
    const auto* screen = UI_ROOT->GetChildStaticCast<UIElement>(String("Screen"));

    gamelist_ = screen->GetChildStaticCast<Gamelist>(String("Game List"));
    ASSERT_CPP(gamelist_!=nullptr, " can not found Game List");
    SubscribeToEvent(gamelist_, E_ITEMCHANGED,  URHO3D_HANDLER(GameSettingScreen, HandleGamelistChanged));
    gamelist_->SetSelected(true);
    SetGamelist();

    pageIndicator_ = screen->GetChildStaticCast<Text>(String("Page Indicator"));
    ASSERT_CPP(pageIndicator_!=nullptr, " can not found Page Indicator");

    gameIndicator_ = screen->GetChildStaticCast<Text>(String("Game Indicator"));
    ASSERT_CPP(gameIndicator_!=nullptr, " can not found Game Indicator");

    UpdateGameListValues();
    UpdateGameIndexIndicator();
    UpdatePageIndexIndicator();

    lifeText_ = screen->GetChildStaticCast<Text>(String("Life"));
    ASSERT_CPP(lifeText_!=nullptr, " can not found Life");

    levelText_ = screen->GetChildStaticCast<Text>(String("Level"));
    ASSERT_CPP(levelText_!=nullptr, " can not found Level");

    UpdateLevelListTexts();
}

void GameSettingScreen::Leave()
{
    Screen::Leave();
}

bool GameSettingScreen::HandleKeyDown(InputKey key, int idx)
{
    bool handled;
    handled = Screen::HandleKeyDown(key, idx);
    if (handled) return true;
    handled = gamelist_->HandleKeyDown(key, idx);
    if (handled) return true;

    return false;
}

bool GameSettingScreen::HandleKeyUp(InputKey key, int idx)
{
    Screen::HandleKeyUp(key, idx);
    return false;
}

void GameSettingScreen::HandleGamelistChanged(StringHash eventType, VariantMap& eventData)
{
    UpdatePageIndexIndicator();
    UpdateGameIndexIndicator();
    UpdateLevelListTexts();
}


void GameSettingScreen::SetGamelist()
{
    // clear data
    gamelist_->ClearItems();
    gameInfos_.Clear();

    auto cb = [&](const Machine::GameItem& gameItem)->void{
                {
                    Gamelist::Item item;
                    std::string s = SETTINGS->GetIconPathFormat().CString();
                    item.iconPath_ =  ConstructStringWithFormat(s, gameItem.rom_.CString()).c_str();
                    item.name_ =  gameItem.name_;
                    gamelist_->AddItem(item);
                }
                {
                    GameInfo newGameInfo{gameItem.lifeIdx_, gameItem.validLives_, gameItem.level_};
                    gameInfos_.Push(newGameInfo);
                }
        };

    MACHINE->HandleAllGames(cb);

    // update gamelist
    gamelist_->UpdateDrawItems();
    gamelist_->ResetIndex();
}

void GameSettingScreen::UpdateGameListValues()
{
    totalGames_ = gamelist_->GetGameItemsCount();
    auto pageItems = gamelist_->GetPageItems();
    totalPages_ = int(((totalGames_+pageItems-1)/pageItems));
}

void GameSettingScreen::UpdateGameIndexIndicator()
{
    String s;
    auto index = gamelist_->GetIndex()+1;
    s.AppendWithFormat("%d/%d", index, totalGames_);
    gameIndicator_->SetText(s);
}

void GameSettingScreen::UpdatePageIndexIndicator()
{
    String s;
    auto index = gamelist_->GetIndex()+1;
    auto pageItems = gamelist_->GetPageItems();
    auto pageIndex = (index+pageItems)/pageItems;
    s.AppendWithFormat("%d/%d", pageIndex, totalPages_);
    pageIndicator_->SetText(s);
}

void GameSettingScreen::UpdateLevelListTexts()
{
    auto index = gamelist_->GetIndex();
    const auto& gameInfo = gameInfos_[index];
    if(gameInfo.lifeIdx_ < gameInfo.validLives_.Size()) {
        lifeText_->SetText(String(GetGamelifeString(gameInfo.validLives_[gameInfo.lifeIdx_])));
    }
    else {
        lifeText_->SetText(String(""));
    }

    levelText_->SetText(GetGameLevelString(gameInfo.level_));

}

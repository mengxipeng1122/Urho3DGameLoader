
#include "SettingsScreen.hpp"

void SettingsScreen::Enter()
{

    Screen::Enter();
    auto* uiRoot= context_->GetSubsystem<UI>()->GetRoot();
    auto* screen = uiRoot->CreateChild<UIElement>(GetName());
    auto* cache = context_->GetSubsystem<ResourceCache>(); 
    String fileName= ToString("screens/%s.xml", GetName());
    SharedPtr<File> file = cache->GetFile(fileName); 
    screen->LoadXML(*file);

#define ADD_MENUITEM(TYPE, NAME)                                                     \
    do {                                                                             \
        TYPE* pelem = screen->GetChildStaticCast< TYPE >(String( NAME ));            \
        ASSERT_CPP(pelem!=nullptr, "can not found",NAME);                            \
        menuitems_.Push(WeakPtr<Widget>(pelem));                                     \
    } while(0)
    ADD_MENUITEM( NormalMenuItem, "IO Testing"                   );
    ADD_MENUITEM( NormalMenuItem, "IO Setting"                   );
    ADD_MENUITEM( NormalMenuItem, "USB Start Port"               );
    ADD_MENUITEM( NormalMenuItem, "Game Setting"                 );
    ADD_MENUITEM( NormalMenuItem, "Neogeo Home Training Mode"    );
    ADD_MENUITEM( NormalMenuItem, "Background Music"             );
    ADD_MENUITEM( NormalMenuItem, "Wallpaper"                    );
    ADD_MENUITEM( NormalMenuItem, "Language"                     );
    ADD_MENUITEM( NormalMenuItem, "Network Setting"              );
    ADD_MENUITEM( NormalMenuItem, "Clear Recent List"            );
    ADD_MENUITEM( NormalMenuItem, "Default Setting And Quit"     );
    ADD_MENUITEM( NormalMenuItem, "Save Setting And Quit"        );

    menuIndex_ = 0;
    menuitems_[menuIndex_]->SetSelected(true);
}

void SettingsScreen::Leave()
{
    Screen::Leave();
}

bool SettingsScreen::HandleKeyDown(InputKey key, int idx)
{
    bool handled = menuitems_[menuIndex_]->HandleKeyDown(key, idx);
    if(handled) return true;

    switch(key)
    {
        case InputKey::UP : { 
            menuitems_[menuIndex_]->SetSelected(false);
            if (menuIndex_>0) {
                menuIndex_ --;
            }
            else {
                menuIndex_ = menuitems_.Size()-1;
            }
            menuitems_[menuIndex_]->SetSelected(true);
            return  true;
        }

        case InputKey::DOWN: { 
            menuitems_[menuIndex_]->SetSelected(false);
            menuIndex_ ++;
            menuIndex_ %= menuitems_.Size();
            menuitems_[menuIndex_]->SetSelected(true);
            return  true;
        }
    }
    return false;
}


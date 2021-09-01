
#include "ScreenManager.hpp"


DP::Factory<ScreenManager::ScreenTypes, ScreenBuilder, Screen> ScreenManager::s_screenFactory; 

std::unique_ptr<Screen> ScreenManager::s_currentScreen{nullptr};

ScreenManager::ScreenManager()
{
}

void ScreenManager::setCurrentScreen(ScreenTypes name, Context* context)
{
    if(s_currentScreen!=nullptr)
    {
        s_currentScreen->Leave(context);
        s_currentScreen = nullptr;
    }
    {
        s_currentScreen = std::unique_ptr<Screen>( s_screenFactory.Build(name));
        s_currentScreen->Enter(context);
    }
    return ;
}


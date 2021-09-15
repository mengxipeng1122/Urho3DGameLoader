
#include "ScreenManager.hpp"


DP::Factory<ScreenManager::ScreenTypes, ScreenBuilder, Screen, Context* > ScreenManager::s_screenFactory; 

std::unique_ptr<Screen> ScreenManager::s_currentScreen{nullptr};

ScreenManager::ScreenManager()
{
}

void ScreenManager::SetCurrentScreen(ScreenTypes name, Context* context)
{
    auto  newScreen = std::unique_ptr<Screen>( s_screenFactory.Build(name, context));
    SetCurrentScreen(std::move(newScreen));
    return ;
}

void ScreenManager::SetCurrentScreen(std::unique_ptr<Screen> ptr)
{
    if(s_currentScreen!=nullptr)
    {
        s_currentScreen->Leave();
        s_currentScreen = nullptr;
    }
    s_currentScreen = std::move(ptr);
    if(s_currentScreen!=nullptr)
    {
        s_currentScreen->Enter();
    }
    return ;
}


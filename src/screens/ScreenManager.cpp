
#include "ScreenManager.hpp"


DP::Factory<ScreenManager::ScreenTypes, ScreenBuilder, Screen> ScreenManager::s_screenFactory; 

ScreenManager::ScreenManager()
    : currentScreen_()
{
}

void ScreenManager::setCurrentScreen(ScreenTypes& name)
{
    if(currentScreen_!=nullptr)
    {
        currentScreen_->Leave();
        currentScreen_ = nullptr;
    }
    {
        currentScreen_ = std::unique_ptr<Screen>( s_screenFactory.Build(name));
        currentScreen_->Enter();
    }
    return ;
}


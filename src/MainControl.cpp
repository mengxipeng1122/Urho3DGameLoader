
//
// Copyright (c) 2008-2021 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//


#include "utils/log.hpp"

#include "MainControl.hpp"

#include "subsystems/Machine.hpp"
#include "subsystems/Settings.hpp"
#include "subsystems/InputSystem.hpp"
#include "components/VideoPlayerComponent.hpp"
#include "widgets/PageIndicator.hpp"
#include "widgets/Gamelist.hpp"
#include "widgets/TabSelector.hpp"
#include "widgets/VideoPlayer.hpp"
#include "widgets/SearchEdit.hpp"
#include "screens/ScreenManager.hpp"
#include "screens/HomeScreen.hpp"
#include "screens/IOTestScreen.hpp"

URHO3D_DEFINE_APPLICATION_MAIN(MainControl)

MainControl::MainControl(Context* context) 
    : Application(context)
    , screenJoystickIndex_(M_MAX_UNSIGNED)
    , screenJoystickSettingsIndex_(M_MAX_UNSIGNED)
    , uiRoot_(GetSubsystem<UI>()->GetRoot())
    , wallpaperNames_{
        "wallpaper/00.jpg",
        "wallpaper/01.jpg",
        "wallpaper/02.jpg",
        "wallpaper/03.jpg",
        "wallpaper/04.jpg",
        "wallpaper/05.jpg",
        "wallpaper/06.jpg",
        "wallpaper/07.jpg",
        "wallpaper/08.jpg",
        "wallpaper/09.jpg",
        }
    , background_(nullptr)
    , logo_(nullptr)
{
    RegisterSubsystems();
    RegisterComponents();
    RegisterWidgets();
    RegisterScreens();

}

void MainControl::RegisterScreens()
{
    { std::string name(HomeScreen  ::GetName()); ScreenManager::RegistScreen(name, new ScreenTBuilder<HomeScreen  >()); }
    { std::string name(IOTestScreen::GetName()); ScreenManager::RegistScreen(name, new ScreenTBuilder<IOTestScreen>()); }
}

void MainControl::RegisterWidgets()
{
    Gamelist     ::RegisterObject(context_);
    VideoPlayer  ::RegisterObject(context_);
    PageIndicator::RegisterObject(context_);
    TabSelector  ::RegisterObject(context_);
    SearchEdit   ::RegisterObject(context_);
}

void MainControl::RegisterSubsystems()
{
    context_->RegisterSubsystem(new Global(context_));
    context_->RegisterSubsystem(new Machine(context_));
    context_->RegisterSubsystem(new Settings(context_, "Settings.xml"));
    context_->RegisterSubsystem(new InputSystem(context_));
}

void MainControl::RegisterComponents()
{
    
	VideoPlayerComponent::RegisterObject(context_);
}



void MainControl::Setup()
{
    // Modify engine startup parameters
    engineParameters_[EP_WINDOW_TITLE] = "GameBox";
    engineParameters_[EP_LOG_NAME]     = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN]  = false;
    engineParameters_[EP_HEADLESS]     = false;
    engineParameters_[EP_SOUND]        = true;

    engineParameters_[EP_WINDOW_WIDTH] = 1280;
    engineParameters_[EP_WINDOW_HEIGHT]=  720;

    // Construct a search path to find the resource prefix with two entries:
    // The first entry is an empty path which will be substituted with program/bin directory -- this entry is for binary when it is still in build tree
    // The second and third entries are possible relative paths from the installed program/bin directory to the asset directory -- these entries are for binary when it is in the Urho3D SDK installation location
    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../share/Resources;../share/Urho3D/Resources";

}

void MainControl::CreateUIControls()
{
    auto* cache = GetSubsystem<ResourceCache>(); 
    // show Background
    background_ = new Sprite(context_);
    {
        auto texture = cache->GetResource<Texture2D>(wallpaperNames_[wallpaperno_]);
        background_->SetSize(texture->GetWidth(), texture->GetHeight());
        background_->SetTexture(texture); // Set texture
        background_->SetName(String("background"));
    }
    uiRoot_->AddChild(background_);

    logo_ = new Sprite(context_);
    {
        auto texture = cache->GetResource<Texture2D>("res/logo.png");
        logo_->SetSize(texture->GetWidth(), texture->GetHeight());
        logo_->SetTexture(texture); // Set texture
    }
    uiRoot_->AddChild(logo_);

}

void MainControl::Start()
{
    // resource path 
    auto* cache = GetSubsystem<ResourceCache>(); 
    auto success = cache->AddResourceDir("Resources");

    // initialize laguage 
    {
        Localization* l10n = GetSubsystem<Localization>();
        l10n->LoadJSONFile("localization/StringsCnEn.json");
        l10n->SetLanguage("En");
        LOG_INFOS_CPP(" lang " , l10n->GetNumLanguages());
    }


    // Load XML file containing default UI style sheet
    auto* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");

    // Set the loaded style as default style
    uiRoot_->SetDefaultStyle(style);

    ScreenManager::setCurrentScreen(HomeScreen::GetName(), context_);

    // Create console and debug HUD
    //CreateConsoleAndDebugHud();

    // Subscribe key down event
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(MainControl, HandleKeyDown));
    // Subscribe key up event
    SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(MainControl, HandleKeyUp));
    // Subscribe scene update event
    SubscribeToEvent(E_SCENEUPDATE, URHO3D_HANDLER(MainControl, HandleSceneUpdate));

}

void MainControl::Stop()
{
    engine_->DumpResources(true);
}

void MainControl::CreateConsoleAndDebugHud()
{
    // Get default style
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    XMLFile* xmlFile = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");

    // Create console
    Console* console = engine_->CreateConsole();
    console->SetDefaultStyle(xmlFile);
    console->GetBackground()->SetOpacity(0.8f);

    // Create debug HUD.
    DebugHud* debugHud = engine_->CreateDebugHud();
    debugHud->SetDefaultStyle(xmlFile);
}


void MainControl::HandleKeyUp(StringHash /*eventType*/, VariantMap& eventData)
{
    using namespace KeyUp;

    int key = eventData[P_KEY].GetInt();

    // Close console (if open) or exit when ESC is pressed
    if (key == KEY_ESCAPE)
    {
        ScreenManager::setCurrentScreen(nullptr);
        engine_->Exit();
    }
}

void MainControl::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

    InputKey inputKey;
    if(INPUT_SYSTEM->HasInputKey(eventData, inputKey))
    {
        ScreenManager::HandleKeyDown(inputKey);
    }

    int key = eventData[P_KEY].GetInt();

    // Toggle console with F1
    if (key == KEY_F1)
        GetSubsystem<Console>()->Toggle();

    // Toggle debug HUD with F2
    else if (key == KEY_F2)
        GetSubsystem<DebugHud>()->ToggleAll();

    // Common rendering quality controls, only when UI has no focused element
    else if (!GetSubsystem<UI>()->GetFocusElement())
    {
        Renderer* renderer = GetSubsystem<Renderer>();

        // Switch Screen test
        if (key == '8')
        {
            static bool homescreen = true;
            if(homescreen)
            {
                ScreenManager::setCurrentScreen(IOTestScreen::GetName(), context_);
                homescreen = false;
            }
            else
            {
                ScreenManager::setCurrentScreen(HomeScreen::GetName(), context_);
                homescreen = true;
            }
        }

        // Save UI layout xml file 
        else if (key == '2')
        {
            File saveFile(this->context_, String("/tmp/tt.xml"), FILE_WRITE); uiRoot_->SaveXML(saveFile);
            LOG_INFOS_CPP(" save to /tmp/tt.xml");
        }

        // Take screenshot
        else if (key == '9')
        {
            Graphics* graphics = GetSubsystem<Graphics>();
            Image screenshot(context_);
            graphics->TakeScreenShot(screenshot);
            // Here we save in the Data folder with date and time appended
            screenshot.SavePNG(GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Screenshot_" +
                Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        }
    }
}

void MainControl::HandleSceneUpdate(StringHash /*eventType*/, VariantMap& eventData)
{
}


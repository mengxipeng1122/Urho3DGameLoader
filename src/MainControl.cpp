
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
#include "widgets/WifiList.hpp"
#include "widgets/Gamelist.hpp"
#include "widgets/MenuBar.hpp"
#include "widgets/VideoPlayer.hpp"
#include "widgets/SearchEdit.hpp"
#include "widgets/Widget.hpp"
#include "widgets/NormalMenuItem.hpp"
#include "widgets/SelectMenuItem.hpp"
#include "widgets/TextSelectMenuItem.hpp"
#include "widgets/ImageSelectMenuItem.hpp"
#include "widgets/Keyboard.hpp"
#include "widgets/BlinkText.hpp"
#include "widgets/JoystickDir.hpp"
#include "widgets/JoystickKey.hpp"
#include "screens/ScreenManager.hpp"
#include "screens/KeySettingScreen.hpp"
#include "screens/HomeScreen.hpp"
#include "screens/IOTestScreen.hpp"
#include "screens/SettingsScreen.hpp"
#include "screens/GameSettingScreen.hpp"
#include "screens/WifiScreen.hpp"

URHO3D_DEFINE_APPLICATION_MAIN(MainControl)

MainControl::MainControl(Context* context) 
    : Application(context)
    , screenJoystickIndex_(M_MAX_UNSIGNED)
    , screenJoystickSettingsIndex_(M_MAX_UNSIGNED)
{
}

void MainControl::RegisterScreens()
{
    { std::string name(HomeScreen       ::GetName()); ScreenManager::RegisterScreen(name, new ScreenTBuilder<HomeScreen       >()); }
    { std::string name(SettingsScreen   ::GetName()); ScreenManager::RegisterScreen(name, new ScreenTBuilder<SettingsScreen   >()); }
    { std::string name(IOTestScreen     ::GetName()); ScreenManager::RegisterScreen(name, new ScreenTBuilder<IOTestScreen     >()); }
    { std::string name(KeySettingScreen ::GetName()); ScreenManager::RegisterScreen(name, new ScreenTBuilder<KeySettingScreen >()); }
    { std::string name(GameSettingScreen::GetName()); ScreenManager::RegisterScreen(name, new ScreenTBuilder<GameSettingScreen>()); }
    { std::string name(WifiScreen       ::GetName()); ScreenManager::RegisterScreen(name, new ScreenTBuilder<WifiScreen       >()); }
}

void MainControl::RegisterWidgets()
{
    // should every widget in hierarchy tree
    Gamelist                ::RegisterObject(context_);
    VideoPlayer             ::RegisterObject(context_);
    PageIndicator           ::RegisterObject(context_);
    MenuBar                 ::RegisterObject(context_);
    SearchEdit              ::RegisterObject(context_);
    Keyboard                ::RegisterObject(context_);
    Widget                  ::RegisterObject(context_);
    MenuItem                ::RegisterObject(context_);
    NormalMenuItem          ::RegisterObject(context_);
    SelectMenuItem          ::RegisterObject(context_);
    TextSelectMenuItem      ::RegisterObject(context_);
    ImageSelectMenuItem     ::RegisterObject(context_);
    JoystickDir             ::RegisterObject(context_);
    JoystickKey             ::RegisterObject(context_);
    BlinkText               ::RegisterObject(context_);
    WifiList                ::RegisterObject(context_);
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
    RegisterSubsystems();
    RegisterComponents();
    RegisterWidgets();
    RegisterScreens();
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
    UI_ROOT->SetDefaultStyle(style);

    ScreenManager::SetCurrentScreen(WifiScreen::GetName(), context_);

    // Create console and debug HUD
    CreateConsoleAndDebugHud();

    // Subscribe key down event
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(MainControl, HandleKeyDown));
    // Subscribe key up event
    SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(MainControl, HandleKeyUp));
    // Subscribe scene update event
    // SubscribeToEvent(E_SCENEUPDATE, URHO3D_HANDLER(MainControl, HandleSceneUpdate));

    // SubscribeToEvent(E_JOYSTICKAXISMOVE,    URHO3D_HANDLER(MainControl, HandleJoyStickAxisMove));
    // SubscribeToEvent(E_JOYSTICKBUTTONDOWN,  URHO3D_HANDLER(MainControl, HandleJoyStickButtonDown));

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

    InputKey inputKey;
    int      inputIdx;
    int key = eventData[P_KEY].GetInt();
    // Close console (if open) or exit when ESC is pressed
    if (key == KEY_ESCAPE) {
        ScreenManager::SetCurrentScreen(nullptr);
        engine_->Exit();
    }
}

void MainControl::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

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
        //if (key == '8')
        //{
        //    static bool homescreen = true;
        //    if(homescreen)
        //    {
        //        ScreenManager::SetCurrentScreen(IOTestScreen::GetName(), context_);
        //        homescreen = false;
        //    }
        //    else
        //    {
        //        ScreenManager::SetCurrentScreen(HomeScreen::GetName(), context_);
        //        homescreen = true;
        //    }
        //}
        //else

        // Save UI layout xml file 
        if (key == '2')
        {
            File saveFile(this->context_, String("/tmp/tt.xml"), FILE_WRITE); 
            UI_ROOT->SaveXML(saveFile);
            LOG_INFOS_CPP(" save to /tmp/tt.xml");
        }

        // Take screenshot
        // else if (key == '9')
        // {
        //     Graphics* graphics = GetSubsystem<Graphics>();
        //     Image screenshot(context_);
        //     graphics->TakeScreenShot(screenshot);
        //     // Here we save in the Data folder with date and time appended
        //     screenshot.SavePNG(GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Screenshot_" +
        //         Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        // }
    }
}

void MainControl::HandleSceneUpdate(StringHash /*eventType*/, VariantMap& eventData)
{
}

void MainControl::HandleJoyStickAxisMove(StringHash /*eventType*/, VariantMap& eventData)
{
    using namespace JoystickAxisMove;
    auto joystickID = eventData[P_JOYSTICKID].GetInt();
    auto axis       = eventData[P_AXIS      ].GetInt();
    auto position   = eventData[P_POSITION  ].GetInt();
}

void MainControl::HandleJoyStickButtonDown(StringHash /*eventType*/, VariantMap& eventData)
{
    InputKey inputKey;
    int      inputIdx;
}


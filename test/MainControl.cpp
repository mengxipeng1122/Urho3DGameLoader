
#include "../src/utils/log.hpp"

#include "MainControl.hpp"
#include "subsystems/InputSystem.hpp"


URHO3D_DEFINE_APPLICATION_MAIN(MainControl)

MainControl::MainControl(Context* context) 
    : Application(context)
    , screenJoystickIndex_(M_MAX_UNSIGNED)
    , screenJoystickSettingsIndex_(M_MAX_UNSIGNED)
{
    RegisterSubsystems();
    RegisterComponents();
    RegisterWidgets();
    RegisterScreens();
}

void MainControl::RegisterScreens()
{
//    { std::string name(HomeScreen       ::GetName()); ScreenManager::RegisterScreen(name, new ScreenTBuilder<HomeScreen       >()); }
}

void MainControl::RegisterWidgets()
{
    // should every widget in hierarchy tree
    // JoystickKey             ::RegisterObject(context_);
}

void MainControl::RegisterSubsystems()
{
    for(auto fun : g_allSubsystemRegisterFuns) fun(context_);
        
//    context_->RegisterSubsystem(new InputSystem(context_));
}

void MainControl::RegisterComponents()
{
	//VideoPlayerComponent::RegisterObject(context_);
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

void MainControl::Start()
{
    // resource path 
    auto success = CACHE->AddResourceDir("Resources");

    // Load XML file containing default UI style sheet
    auto* style = CACHE->GetResource<XMLFile>("UI/DefaultStyle.xml");

    // Set the loaded style as default style
    UI_ROOT->SetDefaultStyle(style);

    // Subscribe key down event
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(MainControl, HandleKeyDown));
    // Subscribe key up event
    SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(MainControl, HandleKeyUp));
    // Subscribe scene update event
    SubscribeToEvent(E_SCENEUPDATE, URHO3D_HANDLER(MainControl, HandleSceneUpdate));

    SubscribeToEvent(E_JOYSTICKAXISMOVE,    URHO3D_HANDLER(MainControl, HandleJoyStickAxisMove));
    SubscribeToEvent(E_JOYSTICKBUTTONDOWN,  URHO3D_HANDLER(MainControl, HandleJoyStickButtonDown));

}

void MainControl::Stop()
{
    engine_->DumpResources(true);
}

void MainControl::HandleKeyUp(StringHash /*eventType*/, VariantMap& eventData)
{
    using namespace KeyUp;

    InputKey inputKey;
    int      inputIdx;
    int key = eventData[P_KEY].GetInt();
    // Close console (if open) or exit when ESC is pressed
    if (key == KEY_ESCAPE)
    {
        engine_->Exit();
    }
}

void MainControl::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

    InputKey inputKey;
    int      inputIdx;
    int key = eventData[P_KEY].GetInt();
    LOG_INFOS_CPP("key", key);

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


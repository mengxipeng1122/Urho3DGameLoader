#pragma once

#include "Global.h"
#include "Settings.hpp"


/// MainControl class, as framework for all samples.
///    - Initialization of the Urho3D engine (in Application class)
///    - Modify engine parameters for windowed mode and to show the class name as title
///    - Create Urho3D logo at screen
///    - Set custom window title and icon
///    - Create Console and Debug HUD, and use F1 and F2 key to toggle them
///    - Toggle rendering options from the keys 1-8
///    - Take screenshot with key 9
///    - Handle Esc key down to hide Console or exit application
///    - Init touch input on mobile platform using screen joysticks (patched for each individual sample)
class MainControl : public Application
{
    // Enable type information.
    URHO3D_OBJECT(MainControl, Application);

public:
    /// Construct.
    explicit MainControl(Context* context);

    /// Setup before engine initialization. Modifies the engine parameters.
    void Setup() override;
    /// Setup after engine initialization. Creates the logo, console & debug HUD.
    void Start() override;
    /// Cleanup after the main loop. Called by Application.
    void Stop() override;

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    virtual String GetScreenJoystickPatchString() const { return String::EMPTY; }


private:
    /// Create console and debug HUD.
    void CreateConsoleAndDebugHud();
    /// Handle key down event to process key controls common to all samples.
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
    /// Handle key up event to process key controls common to all samples.
    void HandleKeyUp(StringHash eventType, VariantMap& eventData);
    /// Handle scene update event to control camera's pitch and yaw for all samples.
    void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);

    /// Screen joystick index for navigational controls (mobile platforms only).
    unsigned screenJoystickIndex_;
    /// Screen joystick index for settings (mobile platforms only).
    unsigned screenJoystickSettingsIndex_;

    ////////////////////////////////////////////////////////////////////////////////
    // setttings
    Settings settings_;
    ////////////////////////////////////////////////////////////////////////////////
    // screens
    void RegisterSubsystems();
    void RegisterScreens();
    void RegisterWidgets();
    void RegisterComponents();
    

    // uiroot 
    SharedPtr<UIElement> uiRoot_;
    void CreateUIControls();
    ////////////////////////////////////////////////////////////////////////////////
    /// wallpaper names
    Vector<String> wallpaperNames_;
    size_t wallpaperno_{0};
    /// background
    SharedPtr<Sprite> background_;

    /// logo
    SharedPtr<Sprite> logo_;

};

//#include "MainControl.inl"

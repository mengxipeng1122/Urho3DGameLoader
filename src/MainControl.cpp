
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

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/UI/BorderImage.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/IO/Log.h>

#include "utils/log.hpp"

#include "MainControl.hpp"

URHO3D_DEFINE_APPLICATION_MAIN(MainControl)

MainControl::MainControl(Context* context) 
    : Application(context)
    , yaw_(0.0f)
    , pitch_(0.0f)
    , touchEnabled_(false)
    , useMouseMode_(MM_ABSOLUTE)
    , screenJoystickIndex_(M_MAX_UNSIGNED)
    , screenJoystickSettingsIndex_(M_MAX_UNSIGNED)
    , paused_(false)
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
}

void MainControl::Setup()
{
    // Modify engine startup parameters
    engineParameters_[EP_WINDOW_TITLE] = "GameBox";
    engineParameters_[EP_LOG_NAME]     = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN]  = false;
    engineParameters_[EP_HEADLESS]     = false;
    engineParameters_[EP_SOUND]        = false;

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
    auto success = cache->AddResourceDir("../Resources");
  //  if (GetSubsystem<Input>()->GetNumJoysticks() == 0) SubscribeToEvent(E_TOUCHBEGIN, URHO3D_HANDLER(MainControl, HandleTouchBegin));


    // Load XML file containing default UI style sheet
    auto* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");

    // Set the loaded style as default style
    uiRoot_->SetDefaultStyle(style);

    if(1)
    {
        SharedPtr<File> file = cache->GetFile("screens/home.xml"); uiRoot_->LoadXML(*file);

        if(0)
        {
            auto sprite = new Sprite(context_);
            auto texture = cache->GetResource<Texture2D>("res/logo.png");
            sprite->SetSize(texture->GetWidth(), texture->GetHeight());
            sprite->SetPosition(391, 0);
            sprite->SetBlendMode(BLEND_ALPHA);
            sprite->SetTexture(texture); // Set texture
            uiRoot_->AddChild(sprite);
        }

        File saveFile(this->context_, String("/tmp/tt.xml"), FILE_WRITE); uiRoot_->SaveXML(saveFile);
    }
    else
    {
        CreateUIControls();
       File saveFile(this->context_, String("/tmp/tt.xml"), FILE_WRITE); uiRoot_->SaveXML(saveFile);
    }



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

void MainControl::InitTouchInput()
{
    touchEnabled_ = true;

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Input* input = GetSubsystem<Input>();
    XMLFile* layout = cache->GetResource<XMLFile>("UI/ScreenJoystick_Samples.xml");
    const String& patchString = GetScreenJoystickPatchString();
    if (!patchString.Empty())
    {
        // Patch the screen joystick layout further on demand
        SharedPtr<XMLFile> patchFile(new XMLFile(context_));
        if (patchFile->FromString(patchString))
            layout->Patch(patchFile);
    }
    screenJoystickIndex_ = (unsigned)input->AddScreenJoystick(layout, cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));
    input->SetScreenJoystickVisible(screenJoystickSettingsIndex_, true);
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
        engine_->Exit();
    }
}

void MainControl::HandleKeyDown(StringHash /*eventType*/, VariantMap& eventData)
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

        // Preferences / Pause
        if (key == KEY_SELECT && touchEnabled_)
        {
            paused_ = !paused_;

            Input* input = GetSubsystem<Input>();
            if (screenJoystickSettingsIndex_ == M_MAX_UNSIGNED)
            {
                // Lazy initialization
                ResourceCache* cache = GetSubsystem<ResourceCache>();
                screenJoystickSettingsIndex_ = (unsigned)input->AddScreenJoystick(cache->GetResource<XMLFile>("UI/ScreenJoystickSettings_Samples.xml"), cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));
            }
            else
                input->SetScreenJoystickVisible(screenJoystickSettingsIndex_, paused_);
        }

        // Texture quality
        else if (key == '1')
        {
            auto quality = (unsigned)renderer->GetTextureQuality();
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            renderer->SetTextureQuality((MaterialQuality)quality);
        }

        // Material quality
        else if (key == '2')
        {
            auto quality = (unsigned)renderer->GetMaterialQuality();
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            renderer->SetMaterialQuality((MaterialQuality)quality);
        }

        // Specular lighting
        else if (key == '3')
            renderer->SetSpecularLighting(!renderer->GetSpecularLighting());

        // Shadow rendering
        else if (key == '4')
            renderer->SetDrawShadows(!renderer->GetDrawShadows());

        // Shadow map resolution
        else if (key == '5')
        {
            int shadowMapSize = renderer->GetShadowMapSize();
            shadowMapSize *= 2;
            if (shadowMapSize > 2048)
                shadowMapSize = 512;
            renderer->SetShadowMapSize(shadowMapSize);
        }

        // Shadow depth and filtering quality
        else if (key == '6')
        {
            ShadowQuality quality = renderer->GetShadowQuality();
            quality = (ShadowQuality)(quality + 1);
            if (quality > SHADOWQUALITY_BLUR_VSM)
                quality = SHADOWQUALITY_SIMPLE_16BIT;
            renderer->SetShadowQuality(quality);
        }

        // Occlusion culling
        else if (key == '7')
        {
            bool occlusion = renderer->GetMaxOccluderTriangles() > 0;
            occlusion = !occlusion;
            renderer->SetMaxOccluderTriangles(occlusion ? 5000 : 0);
        }

        // Instancing
        else if (key == '8')
            renderer->SetDynamicInstancing(!renderer->GetDynamicInstancing());

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

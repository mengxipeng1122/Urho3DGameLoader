#pragma once
#include "Urho3DAll.h"


// all shortcuts for subsystem
// urho3d related
#define CACHE       GetSubsystem<ResourceCache>()
#define GLOBAL      GetSubsystem<Global>()
#define INPUT       GetSubsystem<Input>()
#define UI_ROOT     GetSubsystem<UI>()->GetRoot()
#define RENDERER    GetSubsystem<Renderer>()

////////////////////////////////////////////////////////////////////////////////
// applications
#include "subsystems/Settings.hpp"
#include "subsystems/Machine.hpp"
#include "subsystems/InputSystem.hpp"
#define SETTINGS        GetSubsystem<Settings>()
#define MACHINE         GetSubsystem<Machine>()
#define INPUT_SYSTEM    GetSubsystem<InputSystem>()


class Global : public Object
{
    URHO3D_OBJECT(Global, Object);

public:
    Global(Context* context);

private:

};


// extension to Urho3D library
// for ostream
std::ostream& operator<< ( std::ostream& os, const Urho3D::String& c );
const Urho3D::String Urho3DStringStrip(const Urho3D::String& s);

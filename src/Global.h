#pragma once
#include "Urho3DAll.h"


// all shortcuts for subsystem
// urho3d related
#define CACHE       GetSubsystem<ResourceCache>()
#define GLOBAL      GetSubsystem<Global>()
#define INPUT       GetSubsystem<Input>()
#define UI_ROOT     GetSubsystem<UI>()->GetRoot()
#define RENDERER    GetSubsystem<Renderer>()
#define L10N        GetSubsystem<Localization>()

////////////////////////////////////////////////////////////////////////////////
// applications
#include "subsystems/Settings.hpp"
#include "subsystems/InputSystem.hpp"
#include "subsystems/Machine.hpp"
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

////////////////////////////////////////////////////////////////////////////////
// events
namespace Urho3D
{


}

// macros
#define DEF_TEXTURE_ATTR_SETTER_GETTER( n0, n1 ) \
    void Set ## n0 ## TextureAttr(const ResourceRef& value) { n1 ## Texture_ = value.name_ ; }  \
    ResourceRef Get ## n0 ## TextureAttr() const { return ResourceRef(Texture2D::GetTypeStatic(), n1 ## Texture_ ); } \

#define DEF_FONT_ATTR_SETTER_GETTER( n0, n1 ) \
    void Set ## n0 ## FontAttr(const ResourceRef& value) { n1 ## Font_ = value.name_ ; }  \
    ResourceRef Get ## n0 ## FontAttr() const { return ResourceRef(Font::GetTypeStatic(), n1 ## Font_ ); } \



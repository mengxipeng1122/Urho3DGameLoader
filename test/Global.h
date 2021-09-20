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

URHO3D_EVENT(E_ITEMCHANGED, ItemChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_INDEX,   Index);                // Integer [in/out]
}

URHO3D_EVENT(E_LOSTSELECTED, LostSelected)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_KEY,     InputKey);             // pressed key;
    URHO3D_PARAM(P_INDEX,   Index);                // Integer [in/out]
}

URHO3D_EVENT(E_STRINGCHANGED,   StringChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_STRING,  String);               // pressed key;
}


}

// macros
#define DEF_TEXTURE_ATTR_SETTER_GETTER( n0, n1 ) \
    void Set ## n0 ## TextureAttr(const ResourceRef& value) { n1 ## Texture_ = value.name_ ; }  \
    ResourceRef Get ## n0 ## TextureAttr() const { return ResourceRef(Texture2D::GetTypeStatic(), n1 ## Texture_ ); } \

#define DEF_FONT_ATTR_SETTER_GETTER( n0, n1 ) \
    void Set ## n0 ## FontAttr(const ResourceRef& value) { n1 ## Font_ = value.name_ ; }  \
    ResourceRef Get ## n0 ## FontAttr() const { return ResourceRef(Font::GetTypeStatic(), n1 ## Font_ ); } \

extern Vector<std::function<void(Context*)>> g_allSubsystemRegisterFuns;


////////////////////////////////////////////////////////////////////////////////
// applications
// #include "subsystems/Settings.hpp"
// #define SETTINGS        GetSubsystem<Settings>()
// #include "subsystems/Machine.hpp"
// #define MACHINE         GetSubsystem<Machine>()
#include "subsystems/InputSystem.hpp"
#define INPUT_SYSTEM    GetSubsystem<InputSystem>()


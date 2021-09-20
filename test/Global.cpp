
#include "Global.h"

Global::Global(Context* context) 
    : Object(context)
{
}

std::ostream& operator<< ( std::ostream& os, const Urho3D::String& c ) 
{ 
    os <<std::string(c.CString());
    return os; 
}

const Urho3D::String Urho3DStringStrip(const Urho3D::String& s)
{
    Urho3D::String ret = s.Trimmed();

    // strip leading newline/cartridge characters
    while(ret.Length()>0)
    {
        if(    ret[0] == '\n' || ret[0] == '\r') { ret =  ret.Substring(1); }
        else break;
    }
    // strip tail newline/cartridge characters
    while(ret.Length()>0)
    {
        auto leng= ret.Length();
        if(    ret[leng-1] == '\n' || ret[leng-1] == '\r') { ret =  ret.Substring(0, leng-1); }
        else break;
    }

    return ret;
}

Vector<std::function<void(Context*)>> g_allSubsystemRegisterFuns;

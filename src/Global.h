#pragma once
#include "Urho3DAll.h"


// Макросы для более лаконичного кода.
#define CACHE GetSubsystem<ResourceCache>()
#define GLOBAL GetSubsystem<Global>()
#define INPUT GetSubsystem<Input>()
#define UI_ROOT GetSubsystem<UI>()->GetRoot()
#define RENDERER GetSubsystem<Renderer>()


// Собственная подсистема для доступа к глобальным переменным и методам.
class Global : public Object
{
    URHO3D_OBJECT(Global, Object);

public:
    Global(Context* context);

private:

};

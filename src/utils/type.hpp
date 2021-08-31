
#pragma once
#include <string>

// default implementation
template <typename T>
struct TypeName
{
    static std::string Get();
};

// usage:
//const char* name = TypeName<MyType>::Get();

#include "type.inl"


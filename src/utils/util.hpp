
#pragma once 


#pragma once 

#include <string.h>
#include <string>
std::string demangle(char const* mangled);


#include "trace_parser.hpp"
#include <nlohmann/json.hpp>
using json=nlohmann::json;
//////////////////////////////////////////////////////////////////////////////// 
// write json to a file 
void saveJsonToFile(const json& j, const os::String& fn);
void saveJsonToFile(const json& j, const char* fn);
////////////////////////////////////////////////////////////////////////////////
// hexdump
void hexdump(void *ptr, int buflen);

////////////////////////////////////////////////////////////////////////////////
// template for debug 

/*
template<typename T, typename... Args>
void _log(T t, Args... args) // recursive variadic function

#define LOG_INFOS_CPP(T,args...)
#define LOG_ERRS_CPP(T,args...)                                                            
#define ASSERT_CPP(x, fmt, args...) 
*/
#include "mytool_util.inc"

////////////////////////////////////////////////////////////////////////////////
// expand 
//namespace mytools
//{
//    struct EnumValue: public trace::EnumValue
//    {
//        bool operator<(const EnumValue &o)  const {   
//            return value < o.value;                   
//        }                                             
//        bool operator==(const EnumValue &o)  const {  
//            return value == o.value;                  
//        }
//    };
//
//}

// default implementation
template <typename T>
struct TypeName
{
    static const char* Get();
    {
        return typeid(T).name();
    }
};

// usage:
//const char* name = TypeName<MyType>::Get();

#include "util.inl"


#pragma once 

#include <string>
#include <memory>
#include <iomanip>

template<typename ... Args>
std::string ConstructStringWithFormat( const std::string& format, Args ... args );

template<typename ... Args>
std::string ConstructString( const std::string& format, Args ... args );

#include "string.inl"




#pragma once 

#include <iostream>
#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_INFOS(fmt, args...)                                                       \
do{                                                                                   \
    fprintf(stdout, "[%s:%d@%s]" fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##args); \
    fflush(stdout);                                                                   \
} while(0)

#define LOG_ERRS(fmt, args...)                                                        \
do{                                                                                   \
    fprintf(stderr, "[%s:%d@%s:%d:%s]" fmt "\n", __FILE__, __LINE__, __FUNCTION__, errno, strerror(errno), ##args); \
    fflush(stderr);                                                                   \
    exit(-errno);                                                                     \
} while(0)

#define ASSERT(x, fmt, args...)                                                       \
do{                                                                                   \
    if(!(x))LOG_ERRS(fmt, ##args);                                                    \
} while(0)


void _log();

// must have a function with no argument for variadic function 
template<typename T, typename... Args>
void _log(T t, Args... args); // recursive variadic function

#define LOG_INFOS_CPP(T,args...)                                                            \
do{                                                                                         \
    using namespace date;                                                                   \
    std::cout << "[" << std::string(__FILE__) << ":" << std::to_string(__LINE__);           \
    std::cout << "@" << std::string(__FUNCTION__) << "@";                                   \
    std::cout << "@" << std::string(__FUNCTION__) << "@";                                   \
    std::cout << std::chrono::system_clock::now() << "]";                                   \
    _log(T, ##args );                                                                       \
}while(0)

#define LOG_ERRS_CPP(T,args...)                                                             \
do{                                                                                         \
    using namespace date;                                                                   \
    std::cerr << "[" << std::string(__FILE__) << ":" << std::to_string(__LINE__);           \
    std::cout << "@" << std::chrono::system_clock::now();                                   \
    std::cerr << "@" << std::string(__FUNCTION__);                                          \
    std::cerr << ":" << errno;                                                              \
    std::cerr << ":" << strerror(errno) << "]";                                             \
    _log(T, ##args );                                                                       \
    exit(-errno);                                                                           \
}while(0)

#define ASSERT_CPP(x, fmt, args...)                                                         \
do                                                                                          \
{                                                                                           \
    if(!(x)) LOG_ERRS_CPP(fmt, ##args);                                                     \
}while(0)

#include "log.inl"

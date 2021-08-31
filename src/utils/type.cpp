
#include <typeinfo>
#include <cstdlib>
#include <string>
#include <memory>
#include <cxxabi.h>

#include "log.hpp"
#include "type.hpp"

std::string demangle(char const* mangled) {
    auto ptr = std::unique_ptr<char, decltype(& std::free)>{
        abi::__cxa_demangle(mangled, nullptr, nullptr, nullptr),
        std::free
    };
    return {ptr.get()};
}

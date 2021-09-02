# Set project name
project (UrhoGame)
# Define target name
set (TARGET_NAME UrhoGame)

######################################

# Set CMake minimum version and CMake policy required by UrhoCommon module
cmake_minimum_required (VERSION 3.10.2)
if (COMMAND cmake_policy)
    # Disallow use of the LOCATION target property - so we set to OLD as we still need it
    cmake_policy (SET CMP0026 OLD)
    # Honor the visibility properties for SHARED target types only
    cmake_policy (SET CMP0063 OLD)
endif ()
message("CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME} ${CMAKE_CURRENT_LIST_FILE} ${CMAKE_CURRENT_LIST_LINE}")
if (CMAKE_SYSTEM_NAME STREQUAL Linux)
else()
    # Set CMake modules search path
    set(URHO3D_BASE_INCLUDE_DIR ${URHO3D_HOME}/build.mac/include/Urho3D ) 
    set(URHO3D_LIBRARIES ${URHO3D_HOME}/../Urho3D/build.mac/lib/libUrho3D.a ) 
endif()
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules/)
# Include Urho3D Cmake common module
include (UrhoCommon)
# Define source files

file (GLOB SRC_CPP_FILES 
    src/*.cpp
    src/utils/*.cpp
    src/screens/*.cpp
    src/widgets/*.cpp
    )
file (GLOB SRC_H_FILES 
    src/*.hpp
    src/utils/*.hpp
    src/screens/*.hpp
    src/widgets/*.hpp
    )
define_source_files (GROUP EXTRA_CPP_FILES ${SRC_CPP_FILES} EXTRA_H_FILES ${SRC_H_FILES})
#define_source_files ()
# Setup target with resource copying
setup_main_executable ()

get_target_property(TARGET_INCLUDES ${TARGET_NAME} INCLUDE_DIRECTORIES)
list(REMOVE_ITEM TARGET_INCLUDES "/usr/local/include")
list(APPEND TARGET_INCLUDES "/usr/local/include" )
set_target_properties(${TARGET_NAME}  PROPERTIES INCLUDE_DIRECTORIES "${TARGET_INCLUDES}")
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)


add_subdirectory(Samples/61_UITest)




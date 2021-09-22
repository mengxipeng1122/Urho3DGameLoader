
#find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
#include_directories (../src)
#add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (Test 
    MainControl.cpp
    Global.cpp
    subsystems/InputSystem.cpp
    ../src/utils/log.cpp
    )
target_link_libraries (Test 
    /usr/local/lib/Urho3D/libUrho3D.a 
    -ldl
    -lm
    -lrt
    -lGL
    -lavformat
    -lavcodec
    -lavutil
    )
add_test (NAME MyTest COMMAND Test)

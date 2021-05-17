set(HEADER_LIST "../../include/manager/manager.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(manager manager.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(manager PUBLIC ../../include/)

target_link_libraries(manager PRIVATE socket)

# All users of this library will need at least C++11
target_compile_features(manager PUBLIC cxx_std_11)

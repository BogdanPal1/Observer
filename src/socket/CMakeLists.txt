set(HEADER_LIST "../../include/socket/socket.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(socket socket.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(socket PUBLIC ../../include/)

# All users of this library will need at least C++14
target_compile_features(socket PUBLIC cxx_std_14)

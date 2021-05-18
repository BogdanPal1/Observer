set(HEADER_LIST "../../include/buffer/buffer.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(buffer buffer.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(buffer PUBLIC ../../include/)

# All users of this library will need at least C++14
target_compile_features(buffer PUBLIC cxx_std_14)

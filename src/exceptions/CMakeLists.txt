set(HEADER_LIST "../../include/exceptions/exceptions.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(exceptions exceptions.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(exceptions PUBLIC ../../include/)

# All users of this library will need at least C++14
target_compile_features(exceptions PUBLIC cxx_std_14)

set(HEADER_LIST "../../include/ethr/ethernetheader.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(ethernetheader ethernetheader.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(ethernetheader PUBLIC ../include)

# All users of this library will need at least C++11
target_compile_features(ethernetheader PUBLIC cxx_std_11)
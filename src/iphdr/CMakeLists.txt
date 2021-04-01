set(HEADER_LIST "../../include/iphdr/ipheader.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(ipheader ipheader.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(ipheader PUBLIC ../../include/)

# All users of this library will need at least C++11
target_compile_features(ipheader PUBLIC cxx_std_11)
set(HEADER_LIST "../../include/parser/parser.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(parser parser.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(parser PUBLIC ../../include/)

target_link_libraries(parser PRIVATE ethernetheader ipheader)

# All users of this library will need at least C++14
target_compile_features(parser PUBLIC cxx_std_14)

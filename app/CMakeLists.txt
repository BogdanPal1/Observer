add_executable(analyzer main.cpp)

set(CMAKE_CXX_FLAGS "-g")

target_compile_features(analyzer PRIVATE cxx_std_11)

target_link_libraries(analyzer PRIVATE socket ethernetheader buffer ipheader observer)
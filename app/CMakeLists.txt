add_executable(observer main.cpp)

set(CMAKE_CXX_FLAGS "-g")

target_compile_features(observer PRIVATE cxx_std_11)

target_link_libraries(observer PRIVATE socket ethernetheader buffer ipheader manager exceptions)

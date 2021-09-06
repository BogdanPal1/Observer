add_executable(observer main.cpp)

target_compile_features(observer PRIVATE cxx_std_14)

target_link_libraries(observer PRIVATE socket ethernetheader buffer ipheader manager exceptions)

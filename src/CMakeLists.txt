add_library(swzcpu swzcpu.cpp swzcpu.hpp)
add_executable(Example example.cpp)
target_link_libraries(Example PRIVATE swzcpu)
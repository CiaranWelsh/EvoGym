#pybind11_add_module(pybind_example example.cpp)
add_library(pybind_example2 SHARED example.cpp)
target_link_libraries(pybind_example2 pybind11::headers pybind11::module)
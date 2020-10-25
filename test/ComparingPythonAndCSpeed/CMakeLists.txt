add_executable(InCpp in_cpp.cpp)
target_link_libraries(InCpp roadrunner-static::roadrunner-static)

#add_executable(InPybind in_pybind.cpp)
#target_link_libraries(InPybind )

pybind11_add_module(InPybind MODULE in_pybind/in_pybind.cpp)
target_link_libraries(InPybind PRIVATE roadrunner-static::roadrunner-static)












# NumCpp is a header only library and dependency of stats
set(NUMCPP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/NumCpp/include")
set(NUMCPP_INCLUDE_DIR ${NUMCPP_INCLUDE_DIR} PARENT_SCOPE)


# note for when you port to windows. from pybind11 docs:
#    To use the C++17 in Visual Studio 2017 (MSVC 14.1), pybind11 requires the flag /permissive- to be passed to the compiler to enforce standard conformance. When building with Visual Studio 2019, this is not strictly necessary, but still adviced.
add_subdirectory(pybind11)









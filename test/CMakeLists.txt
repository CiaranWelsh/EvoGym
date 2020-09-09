
add_subdirectory(googletest)

set(TEST_EXECUTABLES)

macro(add_test_executable BINARY)
    add_executable(${BINARY} ${ARGN})
#    target_compile_definitions(${BINARY})
    target_link_libraries(${BINARY} PRIVATE
            evo-gym-static
            roadrunner-static::roadrunner-static
            gtest gtest_main
            sbml-static
            )
    target_include_directories(
            ${BINARY} PRIVATE
            $<BUILD_INTERFACE:${EVOGYM_SOURCE_DIR}>
            $<BUILD_INTERFACE:${EVOGYM_INCLUDE_DIR}>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<BUILD_INTERFACE:${STATS_INCLUDE_DIR}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
    target_compile_definitions(${BINARY} PRIVATE EVOGYM_STATIC_DEFINE LIBSBML_STATIC)
    add_dependencies(${BINARY} roadrunner-static::roadrunner-static)
    set(TEST_EXECUTABLES ${TEST_EXECUTABLES} ${BINARY})
endmacro()

#
add_test_executable(NetworkGenerationOptionsTests NetworkGenerationOptionsTests.cpp)
add_test_executable(Messaround messaround.cpp)
add_test_executable(RateLawTests RateLawTests.cpp)

















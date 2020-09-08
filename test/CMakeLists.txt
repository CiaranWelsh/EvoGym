
set(TEST_EXECUTABLES)

macro(add_test_executable BINARY)
    add_executable(${BINARY} ${ARGN})
    target_link_libraries(${BINARY} PRIVATE roadrunner-static::roadrunner-static gtest gtest_main)
    target_include_directories(
            ${BINARY} PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
    set(TEST_EXECUTABLES ${TEST_EXECUTABLES} ${BINARY})
endmacro()

add_test_executable(TestTest main.cpp)

















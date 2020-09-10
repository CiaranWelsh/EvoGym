
add_subdirectory(googletest)

set(TEST_EXECUTABLES)

macro(add_test_executable BINARY)
    add_executable(${BINARY} ${ARGN})
    target_link_libraries(${BINARY} PRIVATE
            evo-gym-static
            roadrunner-static::roadrunner-static
            gtest gtest_main
            sbml-static
            )

    # The evo-gym-static target include directories
    # and compile definitions are
    # public and therefore transitive. --> no needed here.
    # *but the IDE strugles to give me autocomplete
    target_include_directories(${BINARY} PRIVATE
            D:/EvoGym/third_party/NumCpp/include
            )
    add_dependencies(${BINARY} evo-gym-static roadrunner-static::roadrunner-static)
    set(TEST_EXECUTABLES ${TEST_EXECUTABLES} ${BINARY})
endmacro()

#
add_test_executable(NetworkGenerationOptionsTests NetworkGenerationOptionsTests.cpp)
add_test_executable(Messaround messaround.cpp)
add_test_executable(RateLawTests RateLawTests.cpp)
add_test_executable(IdGenTests IdGenTests.cpp)
add_test_executable(RandomNetworksTests RandomNetworkGeneratorTests.cpp)

















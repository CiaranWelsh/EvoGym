
add_subdirectory(googletest)

set(TEST_EXECUTABLES)

macro(add_test_executable BINARY LINK_WITH_GOOGLETEST)
    add_executable(${BINARY} ${ARGN})

    set(LINK_LIBRARIES
            evo-gym-static
            roadrunner-static::roadrunner-static
            sbml-static
            /usr/local/lib/libmpi.dylib
            )
    if (${LINK_WITH_GOOGLETEST})
        set(LINK_LIBRARIES ${LINK_LIBRARIES} gtest gtest_main)
    endif ()


    target_link_libraries(${BINARY} PRIVATE ${LINK_LIBRARIES})


    # The evo-gym-static target include directories
    # and compile definitions are
    # public and therefore transitive. --> no needed here.
    # *but the IDE strugles to give me autocomplete
    #    target_include_directories(${BINARY} PRIVATE
    #
    #            )

    target_include_directories(${BINARY} PRIVATE "/usr/local/include")
    add_dependencies(${BINARY} evo-gym-static roadrunner-static::roadrunner-static)
    set(TEST_EXECUTABLES ${TEST_EXECUTABLES} ${BINARY})
endmacro()


add_test_executable(
        RandomNetworksTests TRUE
        RandomNetworkGeneratorTests.cpp
        "${EVOGYM_INCLUDE_DIR}/evo/RandomNetworkGenerator.h"
        "${EVOGYM_INCLUDE_DIR}/evo/seed.h"
        "${EVOGYM_SOURCE_DIR}/RandomNetworkGenerator.cpp"
        "${EVOGYM_SOURCE_DIR}/seed.cpp"
        RateLawTests.cpp
        "${EVOGYM_INCLUDE_DIR}/evo/RateLaw.h"
        "${EVOGYM_SOURCE_DIR}/RateLaw.cpp"
        NetworkGenerationOptionsTests.cpp
        "${EVOGYM_INCLUDE_DIR}/evo/RandomNetworkGeneratorOptions.h"
        "${EVOGYM_SOURCE_DIR}/RandomNetworkGeneratorOptions.cpp"
)

add_test_executable(ProfileRandomNetwork OFF profile_random_network_test.cpp)
add_test_executable(NumCppRNG ON NumCppRNGTest.cpp)
add_test_executable(HowLongDoesItTakeToCreate100Networks OFF HowLongDoesItTakeToCreate100Networks.cpp)
add_test_executable(HowLongDoesItTakeToCreate100NetworksParallel OFF HowLongDoesItTakeToCreate100NetworksParallel.cpp)
add_test_executable(HelloMPI OFF hello_mpi.cpp)












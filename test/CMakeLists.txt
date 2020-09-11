
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
#    target_include_directories(${BINARY} PRIVATE
#
#            )
    add_dependencies(${BINARY} evo-gym-static roadrunner-static::roadrunner-static)
    set(TEST_EXECUTABLES ${TEST_EXECUTABLES} ${BINARY})
endmacro()


add_test_executable(
        RandomNetworksTests
        RandomNetworkGeneratorTests.cpp
            "${EVOGYM_INCLUDE_DIR}/evo/RandomNetworkGenerator.h"
            "${EVOGYM_INCLUDE_DIR}/evo/seed.h"
            "${EVOGYM_SOURCE_DIR}/RandomNetworkGenerator.cpp"
            "${EVOGYM_SOURCE_DIR}/seed.cpp"
        RateLawTests.cpp
            "${EVOGYM_INCLUDE_DIR}/evo/RateLaw.h"
            "${EVOGYM_SOURCE_DIR}/RateLaw.cpp"
        NetworkGenerationOptionsTests.cpp
            "${EVOGYM_INCLUDE_DIR}/evo/NetworkGenerationOptions.h"
            "${EVOGYM_SOURCE_DIR}/NetworkGenerationOptions.cpp"
        RandomNumberGeneratorTests.cpp
            "${EVOGYM_INCLUDE_DIR}/evo/RandomNumberGenerator.h"
            "${EVOGYM_SOURCE_DIR}/RandomNumberGenerator.cpp"
)














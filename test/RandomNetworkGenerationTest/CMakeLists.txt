
# Test using googletests for Rate laws
add_test_executable(RateLawTests TRUE TEST_EXECUTABLES RateLawTests.cpp)

# Tests for RandomNetworkGenreationOptions using googletests
add_test_executable(NetworkGenerationOptionsTests TRUE TEST_EXECUTABLES RandomNetworkGenerationOptionsTests.cpp)

add_test_executable(NetworkGenerationTests TRUE TEST_EXECUTABLES RandomNetworkGeneratorTests.cpp)

add_test_executable(UniqueReactionsRandomNetworkGeneratorTests TRUE TEST_EXECUTABLES UniqueReactionsRandomNetworkGeneratorTests.cpp)

add_test_executable(NetworkComponentTests TRUE TEST_EXECUTABLES NetworkComponentTests.cpp)

# propagate TEST_EXECUTABLES upwards
set(TEST_EXECUTABLES ${TEST_EXECUTABLES} PARENT_SCOPE)










#add_test_executable(StoichiometryCounterTests TRUE StoicCounterTests.cpp)

## count instances of stoichiometry matrix to ensure uniform sampling of topology space
#add_test_executable(CountInstancesOfStoichiometryMatrices OFF CountInstancesOfStoichiometryMatrices.cpp)
#
#add_test_executable(NetworkGenerationTestWithMPI OFF GenerateMultipleNetworksWithMPI.cpp)


#add_test_executable(IndividualTests ON IndividualTests.cpp ${MOCKUP_DIR}/MockRandomNetworkGenerator.h)
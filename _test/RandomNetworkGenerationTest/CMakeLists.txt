
# Test using googletests for Rate laws
add_test_executable(RateLawTests TRUE RateLawTests.cpp)

# Tests for RandomNetworkGenreationOptions using googletests
add_test_executable(NetworkGenerationOptionsTests TRUE RandomNetworkGenerationOptionsTests.cpp)

add_test_executable(NetworkGenerationTests TRUE RandomNetworkGeneratorTests.cpp)

add_test_executable(StoichiometryCounterTests TRUE StoicCounterTests.cpp)

# count instances of stoichiometry matrix to ensure uniform sampling of topology space
add_test_executable(CountInstancesOfStoichiometryMatrices OFF CountInstancesOfStoichiometryMatrices.cpp)

add_test_executable(NetworkGenerationTestWithMPI OFF GenerateMultipleNetworksWithMPI.cpp)


add_test_executable(IndividualTests ON IndividualTests.cpp ${MOCKUP_DIR}/MockRandomNetworkGenerator.h)
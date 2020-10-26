####################################################################
#   Build the tests
#

# turn on tests with ctest
enable_testing()

add_subdirectory(googletest)

include(GoogleTest)

set(TEST_EXECUTABLES "")

macro(add_test_executable BINARY LINK_WITH_GOOGLETEST)
    add_executable(${BINARY} ${ARGN})

    set(LINK_LIBRARIES
            random-network-generator-static
            roadrunner-static::roadrunner-static
            sbml-static
            /usr/local/lib/libmpi.dylib
            )
    if (${LINK_WITH_GOOGLETEST})
        set(LINK_LIBRARIES ${LINK_LIBRARIES}
                gtest gtest_main
                gmock gmock_main)
    endif ()

    gtest_add_tests(
            TARGET ${BINARY}
    )

    target_link_libraries(${BINARY} PRIVATE ${LINK_LIBRARIES})

    message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}/Mockups")
    target_include_directories(
            ${BINARY} PRIVATE
            $<TARGET_PROPERTY:random-network-generator-static,INCLUDE_DIRECTORIES>
            "/usr/local/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/Mockups"
            "/Users/ciaranwelsh/Documents/Evogen/test/Mockups"
            "${NUMCPP_INCLUDE_DIR}"
            "/Users/ciaranwelsh/Documents/Evogen/third_party/NumCpp/include"
    )
    add_dependencies(${BINARY} random-network-generator-static roadrunner-static::roadrunner-static)
    list(APPEND TEST_EXECUTABLES ${BINARY})
endmacro()

set(MOCKUP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Mockups")

add_subdirectory(${MOCKUP_DIR})

add_subdirectory(RandomNetworkGenerationTest)

add_custom_target(run-ctest
        COMMAND ${CMAKE_CTEST_COMMAND} --verbose --extra-verbose --progress ${CMAKE_BINARY_DIR}
        )


add_subdirectory(RoadRunnerQuestion)










#add_subdirectory(SOQuestions)
#
#add_subdirectory(ExperimentTests)


#add_test_executable(quick_test OFF quick_test.cpp)
#
#add_test_executable(StringTest ON EvoStringTests.cpp)
#
#add_test_executable(MockingExampe ON MockingExample.cpp)
#add_test_executable(NCRandomSeed ON NCRandomSeed.cpp)



##add_test_executable(ProfileRandomNetwork OFF profile_random_network_test.cpp)
##add_test_executable(NumCppRNG ON NumCppRNGTest.cpp)
#add_test_executable(HowLongDoesItTakeToCreate100Networks OFF HowLongDoesItTakeToCreate100Networks.cpp)
#add_test_executable(HowLongDoesItTakeToCreate100NetworksParallel OFF HowLongDoesItTakeToCreate100NetworksParallel.cpp)
#add_test_executable(HowLongDoesItTakeToCreate100RandomNetworks OFF HowLongDoesItTakeToCreate100RandomNetworks.cpp)
#add_test_executable(HowLongDoesItTakeToCreateNRandomNetworksParallel OFF HowLongDoesItTakeToCreateNRandomNetworksParallel.cpp)
#
#


#add_subdirectory(LearningPybind)
#
#add_subdirectory(ComparingPythonAndCSpeed)

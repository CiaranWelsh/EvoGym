####################################################################
#   Build the tests
#

# turn on tests with ctest
enable_testing()

add_subdirectory(googletest)

include(GoogleTest)


#set(TEST_EXECUTABLES "")
#message(STATUS "TEST_EXECUTABLES1 ${TEST_EXECUTABLES}")

# BINARY: Name of the binary for the test unit you are adding
# LINK_WITH_GOOGLETEST: ON or OFF.
# OUT_VARIABLE: test target will be added into this list
function(add_test_executable BINARY LINK_WITH_GOOGLETEST OUT_VARIABLE)
    add_executable(${BINARY} ${ARGN})

    set(LINK_LIBRARIES
            evogen-rng-static
            roadrunner-static::roadrunner-static
            sbml-static
            )


    if (${LINK_WITH_GOOGLETEST})
        set(LINK_LIBRARIES ${LINK_LIBRARIES}
                gtest gtest_main
                gmock gmock_main)
    endif ()

    if (${HAVE_MPI})
        set(LINK_LIBRARIES ${LINK_LIBRARIES} ${MPI_LIBRARY})
    endif ()

    gtest_add_tests(
            TARGET ${BINARY}
    )

    target_link_libraries(${BINARY} PRIVATE ${LINK_LIBRARIES})

    message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}/Mockups")
    target_include_directories(
            ${BINARY} PRIVATE
            $<TARGET_PROPERTY:evogen-rng-static,INCLUDE_DIRECTORIES>
            "${CMAKE_CURRENT_SOURCE_DIR}/Mockups"
            "${NUMCPP_INCLUDE_DIR}"
    )
    add_dependencies(${BINARY} evogen-rng roadrunner-static::roadrunner-static)

    # Add to an output scoped variable keeping track of binaries we need.
    #    message(STATUS "OUT_VARIABLE ${OUT_VARIABLE}")
    #    message(STATUS "OUT_VARIABLE_inner ${${OUT_VARIABLE}}")
    if ("${${OUT_VARIABLE}}" STREQUAL "")
        set(${OUT_VARIABLE} "${BINARY}" PARENT_SCOPE)
    else ()
        set(${OUT_VARIABLE} "${${OUT_VARIABLE}}" "${BINARY}" PARENT_SCOPE)
    endif ()

    #    set(OUT_VARIABLE ${OUT_VARIABLE} ${BINARY} PARENT_SCOPE)
endfunction()


#set(MOCKUP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Mockups")
#
#add_subdirectory(${MOCKUP_DIR})

add_subdirectory(RandomNetworkGenerationTest)

add_custom_target(run-ctest
        COMMAND ${CMAKE_CTEST_COMMAND} --verbose --extra-verbose --progress ${CMAKE_BINARY_DIR}
        )

add_dependencies(run-ctest ${TEST_EXECUTABLES})


#add_subdirectory(RoadRunnerQuestion)


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

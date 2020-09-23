
add_subdirectory(googletest)

include(GoogleTest)

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

#    gtest_discover_tests(${BINARY})


    target_link_libraries(${BINARY} PRIVATE ${LINK_LIBRARIES})


    target_include_directories(
            ${BINARY} PRIVATE
            $<TARGET_PROPERTY:evo-gym-static,INCLUDE_DIRECTORIES>
            "/usr/local/include")
    add_dependencies(${BINARY} evo-gym-static roadrunner-static::roadrunner-static)
    set(TEST_EXECUTABLES ${TEST_EXECUTABLES} ${BINARY})
endmacro()

add_subdirectory(RandomNetworkGenerationTest)

add_subdirectory(SOQuestions)


##add_test_executable(ProfileRandomNetwork OFF profile_random_network_test.cpp)
##add_test_executable(NumCppRNG ON NumCppRNGTest.cpp)
#add_test_executable(HowLongDoesItTakeToCreate100Networks OFF HowLongDoesItTakeToCreate100Networks.cpp)
#add_test_executable(HowLongDoesItTakeToCreate100NetworksParallel OFF HowLongDoesItTakeToCreate100NetworksParallel.cpp)
#add_test_executable(HowLongDoesItTakeToCreate100RandomNetworks OFF HowLongDoesItTakeToCreate100RandomNetworks.cpp)
#add_test_executable(HowLongDoesItTakeToCreateNRandomNetworksParallel OFF HowLongDoesItTakeToCreateNRandomNetworksParallel.cpp)
#
#
#add_test_executable(quick_test OFF quick_test.cpp)






set(target evo-gym)

set(
        SOURCES
        RandomNetworkGeneratorOptions.cpp
        RateLaw.cpp
        Motif.cpp
        Population.cpp
        RandomNetworkGenerator.cpp
)

set(
        HEADERS
        include/evo/RandomNetworkGeneratorOptions.h
        include/evo/RoleTypes.h
        include/evo/RateLaw.h
        include/evo/Motif.h
        include/evo/Population.h
        include/evo/RandomNetworkGenerator.h
        include/evo/logger.h
        include/evo/StoicCounter.h
)

add_library(${target}-static STATIC ${SOURCES} ${HEADERS})

target_link_libraries(
        ${target}-static
        PUBLIC
        roadrunner-static::roadrunner-static
)

message(STATUS "NUMCPP_INCLUDE_DIR ${NUMCPP_INCLUDE_DIR}")

target_include_directories(
        ${target}-static PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        $<BUILD_INTERFACE:${EVOGYM_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${NUMCPP_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
#add_sanitizers(${target}-static)
add_sanitize_address(${target}-static)

target_compile_definitions(
        ${target}-static PUBLIC EVOGYM_STATIC_DEFINE LIBSBML_STATIC
)

add_library(${target} SHARED ${SOURCES} ${HEADERS} ../test/ProfilingModelBuilding/HowLongDoesItTakeToCreate100Networks.cpp ../test/RandomNetworkGenerationTest/StoicCounterTests.cpp ../test/SOQuestions/WhyCanINotAccessThisArray.cpp ../test/RandomNetworkGenerationTest/CountInstancesOfStoichiometryMatrices.cpp)
target_link_libraries(${target} PUBLIC roadrunner-static::roadrunner-static)
target_include_directories(
        ${target} PUBLIC
        $<BUILD_INTERFACE:${EVOGYM_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

generate_export_header(
        ${target}
        BASE_NAME EVOGYM
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/src/evogym_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/evo)




















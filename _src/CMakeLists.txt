set(target evo-gym)

set(
        SOURCES
        RandomNetworkGeneratorOptions.cpp
        EvoRateLaw.cpp
#        Motif.cpp
#        Population.cpp
        RandomNetworkGenerator.cpp
#        Experiment.cpp
#        CSV.cpp
        EvoString.cpp
#        Individual.cpp
#        ExperimentSet.cpp
#        ObjectiveFunction.cpp
        NetworkComponent.cpp
)

set(
        HEADERS
        include/evo/RandomNetworkGeneratorOptions.h
        include/evo/RoleTypes.h
        include/evo/EvoRateLaw.h
#        include/evo/Motif.h
#        include/evo/Population.h
        include/evo/RandomNetworkGenerator.h
        include/evo/logger.h
        include/evo/StoicCounter.h
#        include/evo/Experiment.h
#        include/evo/CSV.h
        include/evo/EvoString.h
#        include/evo/Individual.h
        include/evo/ExperimentSet.h
#        include/evo/ObjectiveFunction.h
        include/evo/TypeDefs.h
        include/evo/NetworkComponent.h
)

add_library(${target}-static STATIC ${SOURCES} ${HEADERS})

target_link_libraries(
        ${target}-static
        PUBLIC
        roadrunner-static::roadrunner-static
        ${MPI_LIBRARY}
)

message(STATUS "NUMCPP_INCLUDE_DIR ${NUMCPP_INCLUDE_DIR}")

target_include_directories(
        ${target}-static PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        $<BUILD_INTERFACE:${EVOGEN_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${NUMCPP_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${MPI_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
#add_sanitizers(${target}-static)
add_sanitize_address(${target}-static)

target_compile_definitions(
        ${target}-static PUBLIC EVOGEN_STATIC_DEFINE LIBSBML_STATIC
)

add_library(${target} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${target} PUBLIC roadrunner-static::roadrunner-static)
target_include_directories(
        ${target} PUBLIC
        $<BUILD_INTERFACE:${EVOGEN_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# we put the export header in current binary directory under evo so it'll match the install directory
generate_export_header(
        ${target}
        BASE_NAME RANDOM_NETWORK_GENERATOR
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/random_network_generator.h"
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/src/EVOGEN_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/evo)




















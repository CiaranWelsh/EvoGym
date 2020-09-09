set(target evo-gym)

set(
        SOURCES
        NetworkGenerationOptions.cpp
        RateLaw.cpp

)
set(
        HEADERS
        include/evo/NetworkGenerationOptions.h
        include/evo/RoleTypes.h
        include/evo/RateLaw.h
)

add_library(${target}-static STATIC ${SOURCES} ${HEADERS})

target_link_libraries(
        ${target}-static
        PUBLIC roadrunner-static::roadrunner-static
)
target_include_directories(
        ${target}-static PUBLIC
        $<BUILD_INTERFACE:${EVOGYM_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_definitions(
        ${target}-static PUBLIC EVOGYM_STATIC_DEFINE LIBSBML_STATIC)

add_library(${target} SHARED ${SOURCES} ${HEADERS})
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




















set(target evogen-rng)

set(
        SOURCES
        RNGOptions.cpp
        evoRateLaw.cpp
        RNG.cpp
        ../EvoString.cpp
        NetworkComponent.cpp
)

set(
        HEADERS
        RNGOptions.h
        RoleTypes.h
        evoRateLaw.h
        RNG.h
        ../logger.h
        StoicCounter.h
        ../TypeDefs.h
        NetworkComponent.h
        ../EvoString.h
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
        $<BUILD_INTERFACE:${RANDOM_NETWORK_GENERATOR_SOURCE_DIR}>
        $<BUILD_INTERFACE:${NUMCPP_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${BOOST_INSTALL_PREFIX}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
        $<BUILD_INTERFACE:${EVOGEN_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
if (${HAVE_MPI})
    message(STATUS "Linking in MPI libraries")
    target_compile_definitions(${target}-static PUBLIC HAVE_MPI)
    target_include_directories(
            ${target}-static PUBLIC
            ${MPI_INCLUDE_DIR}
    )
    target_link_libraries(
            ${target}-static
            PUBLIC
            ${MPI_LIBRARY}
    )
endif()


add_sanitize_address(${target}-static)

target_compile_definitions(
        ${target}-static PUBLIC RNG_STATIC_DEFINE LIBSBML_STATIC RR_STATIC
)


add_library(${target} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${target} PUBLIC $<TARGET_PROPERTY:${target}-static,LINK_LIBRARIES>)
target_include_directories(
        ${target} PUBLIC
        $<BUILD_INTERFACE:$<TARGET_PROPERTY:${target}-static,INCLUDE_DIRECTORIES>>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_definitions(
        ${target}-static PUBLIC LIBSBML_STATIC RR_STATIC
)


generate_export_header(
        ${target}
        BASE_NAME RNG
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/rng_export.h"
)

pybind11_add_module(evogen MODULE evogen.cpp)
target_link_libraries(evogen PRIVATE roadrunner-static::roadrunner-static evogen-rng-static)
target_include_directories(evogen PRIVATE "$<TARGET_PROPERTY:${target},INCLUDE_DIRECTORIES>")

target_compile_definitions(
        evogen PUBLIC LIBSBML_STATIC RR_STATIC RNG_STATIC_DEFINE
)


# install
install(
        TARGETS ${target}-static ${target}
        COMPONENT RNG
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(TARGETS evogen
        COMPONENT RNG
        LIBRARY DESTINATION ${PYTHON_PACKAGE_INSTALL_PREFIX}
        )

configure_file("${EVOGEN_ROOT}/__init__.py.in" "${CMAKE_BINARY_DIR}/__init__.py")
INSTALL(
        FILES
        "${CMAKE_BINARY_DIR}/__init__.py"
        DESTINATION ${PYTHON_PACKAGE_INSTALL_PREFIX}
)


install(FILES
        "${CMAKE_BINARY_DIR}/VERSION.txt"
        "${EVOGEN_ROOT}/LICENCE.txt"
        "${CMAKE_BINARY_DIR}/setup.py"
        DESTINATION .
        COMPONENT RNG
        )













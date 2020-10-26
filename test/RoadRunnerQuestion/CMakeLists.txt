cmake_minimum_required(VERSION 3.15)
project(Evogen)

set(CMAKE_CXX_STANDARD 17)

if (NOT ROADRUNNER_INSTALL_PREFIX)
    find_path(
            ROADRUNNER_INSTALL_PREFIX
            NAMES
            lib/roadrunner${CMAKE_STATIC_LIBRARY_SUFFIX}
    )
endif ()

if (NOT EXISTS "${ROADRUNNER_INSTALL_PREFIX}/lib/cmake")
    message(FATAL_ERROR "Roadrunner cmake module path not found: \"${ROADRUNNER_INSTALL_PREFIX}/lib/cmake\"")
endif ()

message(STATUS "Roadrunner install prefix: ${ROADRUNNER_INSTALL_PREFIX}")

# for find_package(<...> CONFIG)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${ROADRUNNER_INSTALL_PREFIX}/lib/cmake")

# for include(<...>)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ROADRUNNER_INSTALL_PREFIX}/lib/cmake")

# for include sanitizer module
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/third_party/sanitizers-cmake/cmake")

# put all runtime targets (exe and dll) into bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# put libraries into lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# archives
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)


# Roadrunner deps

find_package(Threads) # for libxml2, FindThreads.cmake is shipped with cmake
find_package(LibLZMA) # for libxml2, LibLZMA.cmake is shipped with cmake
find_package(zlib CONFIG REQUIRED)
find_package(bzip2 CONFIG REQUIRED)
find_package(iconv CONFIG REQUIRED)
find_package(LibXml2 CONFIG REQUIRED)
find_package(sbml-static CONFIG REQUIRED)
find_package(rr-libstruct CONFIG REQUIRED)
find_package(clapack CONFIG REQUIRED)
find_package(nleq1 CONFIG REQUIRED)
find_package(nleq2 CONFIG REQUIRED)
find_package(PocoFoundation CONFIG REQUIRED)
find_package(PocoNet CONFIG REQUIRED)
find_package(Sundials CONFIG REQUIRED)
find_package(LLVM REQUIRED)

# deps
find_package(roadrunner-static CONFIG REQUIRED)


include(GenerateExportHeader)

set(target CreateRRModel)
add_library(${target} SHARED CreateRRModel.h)
target_link_libraries(${target} PUBLIC roadrunner-static::roadrunner-static)
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

generate_export_header(
        ${target}
        BASE_NAME CREATE_RR_MODEL
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/create_rr_model_export.h"
)


add_library(${target}-C-API SHARED CreateRRModelCAPI.cpp)
target_link_libraries(${target}-C-API PUBLIC ${target})

set_target_properties(${target}-C-API PROPERTIES PREFIX "")

generate_export_header(
        ${target}-C-API
        BASE_NAME CREATE_RR_MODEL_C_API
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/create_rr_model_c_api_export.h"
)


file(COPY create_rr_model_api.py DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})



add_executable(TestCPP TestCPP.cpp)
target_link_libraries(TestCPP PRIVATE ${target})

add_executable(TestC TestC.cpp)
target_link_libraries(TestC PRIVATE ${target}-C-API )
#roadrunner-static::roadrunner-static)















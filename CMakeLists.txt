cmake_minimum_required(VERSION 3.15)


set(EVOGEN_VERSION_MAJOR 0)
set(EVOGEN_VERSION_MINOR 0)
set(EVOGEN_VERSION_PATCH 1)

set(EVOGEN_VERSION "${EVOGEN_VERSION_MAJOR}.${EVOGEN_VERSION_MINOR}.${EVOGEN_VERSION_PATCH}")
project(
        Evogen
        DESCRIPTION "Evogen: evolving network topologies"
        VERSION ${EVOGEN_VERSION}
        LANGUAGES CXX C
)

set(EVOGEN_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

configure_file(VERSION.txt.in "${CMAKE_CURRENT_BINARY_DIR}/VERSION.txt")
configure_file(setup.py.in "${CMAKE_CURRENT_BINARY_DIR}/setup.py")

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)

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

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#######################################################################
# includes
#

include(GNUInstallDirs)

include(GenerateExportHeader)

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
find_package(roadrunner-static CONFIG REQUIRED)
find_package(roadrunner CONFIG REQUIRED)
find_package(roadrunner_c_api CONFIG REQUIRED)


# on linux, libz2

add_custom_target(printGenex
        COMMENT "Result of generator expression:"
        COMMAND ${CMAKE_COMMAND} -E echo "cmd here$<TARGET_PROPERTY:roadrunner-static::roadrunner-static,INTERFACE_LINK_LIBRARIES>"
        VERBATIM
        )

find_path(
        BOOST_INSTALL_PREFIX
        NAMES
        boost/algorithm/algorithm.hpp
        lib/cmake/Boost-1.75.0/BoostConfig.cmake
)

message(STATUS "BOOST_INSTALL_PREFIX ${BOOST_INSTALL_PREFIX}")

if (NOT EXISTS ${BOOST_INSTALL_PREFIX})
    message(FATAL_ERROR "Couldn't find Boost. Please provide the root to your boost installation \
using
    -DBOOST_INSTALL_PREFIX=\"/path/to/boost/install/prefix\".
Note, the boost install prefix is the \
folder that contains lib/cmake/BoostConfig.cmake. On mine this is
    /Users/ciaranwelsh/Documents/boost/stage
")
endif ()

message(STATUS "Boost_FOUND: ${Boost_FOUND}")

set(BOOST_INCLUDE_DIR "${BOOST_INSTALL_PREFIX}/boost")
include(CheckIncludeFile)
check_include_file("${BOOST_INCLUDE_DIR}/algorithm/algorithm.h" BOOST_FOUND)
if (NOT ${BOOST_FOUND})
    message(FATAL_ERROR "Boost file ${BOOST_INCLUDE_DIR}/algorithm/algorithm.h cannot be located")
endif ()

find_package(Sanitizers)
find_package(Python COMPONENTS Interpreter Development NumPy REQUIRED)

if (NOT ${PYTHON_FOUND})
    message(FATAL_ERROR "Can't find Python")
endif ()

find_path(
        MPI_INCLUDE_DIR
        NAMES mpi.h
)

find_library(
        MPI_LIBRARY
        NAMES
        mpi${CMAKE_SHARED_LIBRARY_SUFFIX}
        libmpi${CMAKE_SHARED_LIBRARY_SUFFIX}
)
set(HAVE_MPI FALSE)
if (MPI_INCLUDE_DIR_FOUND AND MPI_LIBRARY)
    set(HAVE_MPI TRUE)
endif ()
message(STATUS "HAVE_MPI ${HAVE_MPI}")

#######################################################################
#   options
#


# Hide things by default
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

option(WITH_SANITIZER "Compiler with sanitizers" ON)
set(WHICH_SANITIZER "address" CACHE STRING "Which sanitizer to use")


if (${WITH_SANITIZER} AND ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}"))
    #turn off optimizations for debug builds so profiler results do not get skewed
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -fno-omit-frame-pointer -fsanitize=${WHICH_SANITIZER}")
    set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=${WHICH_SANITIZER}")
endif ()

set(PYTHON_PACKAGE_INSTALL_PREFIX "site-packages/evogen" CACHE STRING "Full or relative path to where to install the Python package. If
relative, then this is relative to the CMAKE_INSTALL_PREFIX variable")

#######################################################################
#   Implement options
#

#add_definitions(
#        -DLIBSBML_USE_CPP_NAMESPACE
#        -DLIBSBML_STATIC
#        -DLIBLAX_STATIC
#        -DSTATIC_LIBSTRUCT
#        -DSTATIC_PUGI
#        -DSTATIC_NLEQ1
#        -DSTATIC_NLEQ2
#        -DPOCO_STATIC
#        -DPOCO_NO_AUTOMATIC_LIBS
#        -DCRT_NONSTDC_NO_DEPRECATE
#        -D_CRT_SECURE_NO_WARNINGS    # MS wanting you to changes basically all standard C functions :(
#        -D_WIN32                     # used as switch in zlib macro
#        -DXML_STATIC                 # for expat inside poco. The code that uses this define (poco_xml) is only used in tests.
#)

# when not windows, add sanitizer flags to debug configuration


#######################################################################
#   Configure dependencies
#

# use the roadrunner defined cmake script for importing roadrunner
# The script hides the find_package calls needed for roadrunner and
# its dependencies.
#include(ImportRoadrunnerAndDependencies)

add_subdirectory(third_party)
#############################################################################
# Add sources and tests to the project
#
set(RANDOM_NETWORK_GENERATOR_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/RandomNetworkGenerator")
set(EVOGEN_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(src)


add_subdirectory(test)


message(STATUS "

------------------------
Configuration Summary
------------------------
CMAKE_CXX_COMPILER          ${CMAKE_CXX_COMPILER}
CMAKE_CXX_COMPILER_ID       ${CMAKE_CXX_COMPILER_ID}
CMAKE_CXX_STANDARD          ${CMAKE_CXX_STANDARD}
WITH_SANITIZER              ${WITH_SANITIZER}
WHICH_SANITIZER             ${WHICH_SANITIZER}
MPI_INCLUDE_DIR             ${MPI_INCLUDE_DIR}
MPI_LIBRARY                 ${MPI_LIBRARY}

--------------------------------------
Python Variables
--------------------------------------
Python_FOUND                        ${Python_FOUND}
Python_Interpreter_FOUND            ${Python_Interpreter_FOUND}
Python_EXECUTABLE                   ${Python_EXECUTABLE}
Python_INTERPRETER_ID               ${Python_INTERPRETER_ID}
Python_STDLIB                       ${Python_STDLIB}
Python_STDARCH                      ${Python_STDARCH}
Python_SITELIB                      ${Python_SITELIB}
Python_SITEARCH                     ${Python_SITEARCH}
Python_SOABI                        ${Python_SOABI}
Python_Compiler_FOUND               ${Python_Compiler_FOUND}
Python_COMPILER                     ${Python_COMPILER}
Python_COMPILER_ID                  ${Python_COMPILER_ID}
IronPython                          ${IronPython}
Python_DOTNET_LAUNCHER              ${Python_DOTNET_LAUNCHER}
Python_Development_FOUND            ${Python_Development_FOUND}
Python_Development.Module_FOUND     ${Python_Development.Module_FOUND}
Python_Development.Embed_FOUND      ${Python_Development.Embed_FOUND}
Python_INCLUDE_DIRS                 ${Python_INCLUDE_DIRS}
Python_LINK_OPTIONS                 ${Python_LINK_OPTIONS}
Python_LIBRARIES                    ${Python_LIBRARIES}
Python_LIBRARY_DIRS                 ${Python_LIBRARY_DIRS}
Python_RUNTIME_LIBRARY_DIRS         ${Python_RUNTIME_LIBRARY_DIRS}
Python_VERSION                      ${Python_VERSION}
Python_VERSION_MAJOR                ${Python_VERSION_MAJOR}
Python_VERSION_MINOR                ${Python_VERSION_MINOR}
Python_VERSION_PATCH                ${Python_VERSION_PATCH}
Python_PyPy_VERSION                 ${Python_PyPy_VERSION}
Python_NumPy_FOUND                  ${Python_NumPy_FOUND}
Python_NumPy_INCLUDE_DIRS           ${Python_NumPy_INCLUDE_DIRS}
Python_NumPy_VERSION                ${Python_NumPy_VERSION}
")















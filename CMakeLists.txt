cmake_minimum_required(VERSION 3.15..3.18)
project(EvoGym)

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

# for find_package(<...> CONFIG)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${ROADRUNNER_INSTALL_PREFIX}/lib/cmake")

# for include(<...>)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ROADRUNNER_INSTALL_PREFIX}/lib/cmake")

# for include sanitizer module
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/third_party/sanitizers-cmake/cmake")
#######################################################################
# includes
#
include(GNUInstallDirs)

include(GenerateExportHeader)

include(ImportRoadrunnerAndDependencies)

find_path(
        BOOST_INSTALL_PREFIX
        NAMES lib/cmake/Boost-1.75.0/BoostConfig.cmake
)

if (NOT EXISTS ${BOOST_INSTALL_PREFIX})
    message(FATAL_ERROR "Couldn't find Boost. Please provide the root to your boost installation \
using
    -DBOOST_INSTALL_PREFIX=\"/path/to/boost/install/prefix\".
Note, the boost install prefix is the \
folder that contains lib/cmake/BoostConfig.cmake. On mine this is
    /Users/ciaranwelsh/Documents/boost/stage
")
endif()
message(STATUS "BOOST_INSTALL_PREFIX ${BOOST_INSTALL_PREFIX}")

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${BOOST_INSTALL_PREFIX}")

# get boost for NumCpp
find_package(Boost REQUIRED CONFIG )
find_package(Sanitizers)

#######################################################################
#   options
#

option(WITH_ADDRESS_SANITIZER "Compile with address sanitizer" OFF)
if (${WITH_ADDRESS_SANITIZER})
    find_package(Sanitizers)
endif ()

# Hide things by default
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
set(CMAKE_CXX_STANDARD 14)

#######################################################################
#   Implement options
#

if (NOT ${WIN32})
    if (${WITH_ADDRESS_SANITIZER})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    endif ()
endif ()


#######################################################################
#   Configure dependencies
#

# use the roadrunner defined cmake script for importing roadrunner
# The script hides the find_package calls needed for roadrunner and
# its dependencies.
include(ImportRoadrunnerAndDependencies)

add_subdirectory(third_party)


#############################################################################
# Add sources and tests to the project
#
set(EVOGYM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/include")
set(EVOGYM_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
add_subdirectory(src)


add_subdirectory(test)





















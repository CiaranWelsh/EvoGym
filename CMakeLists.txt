cmake_minimum_required(VERSION 3.18)
project(EvoGym)

set(CMAKE_CXX_STANDARD 14)


if (NOT ROADRUNNER_INSTALL_PREFIX)
    find_path(
            ROADRUNNER_INSTALL_PREFIX
            NAMES
            lib/roadrunner${CMAKE_STATIC_LIBRARY_SUFFIX}
    )
endif ()

# for find_package(<...> CONFIG)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${ROADRUNNER_INSTALL_PREFIX}/lib/cmake")

# for include(<...>)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ROADRUNNER_INSTALL_PREFIX}/lib/cmake")

#######################################################################
# includes
#
include(GNUInstallDirs)

include(GenerateExportHeader)

include(ImportRoadrunnerAndDependencies)

#######################################################################
#   options
#

option(WITH_ADDRESS_SANITIZER "Compile with address sanitizer" OFF)

# Hide things by default
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

#######################################################################
#   Implement options
#

if (NOT ${WIN32})
    if (${WITH_ADDRESS_SANITIZER})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
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





















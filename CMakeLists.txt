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

# use the roadrunner defined cmake script for importing roadrunner
# The script hides the find_package calls needed for roadrunner and
# its dependencies.
include(ImportRoadrunnerAndDependencies)

add_subdirectory(src)


add_subdirectory(test)


























# stats is a header only library. We just need to include the following to use it.
set(STATS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/stats/include")
set(STATS_INCLUDE_DIR ${STATS_INCLUDE_DIR} PARENT_SCOPE)
# D:\EvoGym\third_party\stats\include
message("STATS_INCLUDE_DIR ${STATS_INCLUDE_DIR}")

## rebuild the stats include directory in the install tree
install(FILES "${STATS_INCLUDE_DIR}/stats.hpp" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# todo use install(DIRECTORY
#install(FILES "${STATS_INCLUDE_DIR}/stats_incl/dens" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/stats_incl/dens")
#install(FILES "${STATS_INCLUDE_DIR}/stats_incl/misc" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/stats_incl/misc")
#install(FILES "${STATS_INCLUDE_DIR}/stats_incl/prob" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/stats_incl/prob")
#install(FILES "${STATS_INCLUDE_DIR}/stats_incl/quant" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/stats_incl/quant")
#install(FILES "${STATS_INCLUDE_DIR}/stats_incl/rand" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/stats_incl/rand")
#

# gcem is a header only library and dependency of stats
set(GCEM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gcem/include")
SET(GCEM_INCLUDE_DIR ${GCEM_INCLUDE_DIR} PARENT_SCOPE)

# rebuild the gcem include directory in the install tree
install(FILES "${GCEM_INCLUDE_DIR}/gcem.hpp" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/gcem")
#install(FILES "${GCEM_INCLUDE_DIR}/gcem_incl/quadrature" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/gcem/gcem_incl/quadrature")
#install(FILES "${GCEM_INCLUDE_DIR}/gcem_incl" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/gcem/gcem_incl")
#

# NumCpp is a header only library and dependency of stats
set(NUMCPP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/NumCpp/include")
SET(NUMCPP_INCLUDE_DIR ${NUMCPP_INCLUDE_DIR} PARENT_SCOPE)

# rebuild the gcem include directory in the install tree
#install(FILES "${NUMCPP_INCLUDE_DIR}/NumCpp.hpp" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/NumCpp")
#install(FILES "${NUMCPP_INCLUDE_DIR}/NumCpp" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/NumCpp")
#install(FILES NumCpp/include/NumCpp/Coordinates DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/NumCpp")
#install(FILES NumCpp/include/NumCpp/Core DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/NumCpp")
#install(FILES NumCpp/include/NumCpp/Filter DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/NumCpp")
#install(FILES NumCpp/include/NumCpp/Functions DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/NumCpp")
#install(FILES NumCpp/include/NumCpp/ImageProcessing DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/NumCpp")
#install(FILES NumCpp/include/NumCpp/Integrate DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/NumCpp")
#install(FILES NumCpp/include/NumCpp/Linalg DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/NumCpp")
#install(FILES NumCpp/include/NumCpp/NdArray DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/NumCpp")
#install(FILES NumCpp/include/NumCpp/Polynomial DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/NumCpp")


















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













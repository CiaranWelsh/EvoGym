

# NumCpp is a header only library and dependency of stats
set(NUMCPP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/NumCpp/include")
SET(NUMCPP_INCLUDE_DIR ${NUMCPP_INCLUDE_DIR} PARENT_SCOPE)




add_subdirectory(DataFrame)
#set(DATAFRAME_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/DataFrame/include")
#set(DATAFRAME_INCLUDE_DIR ${DATAFRAME_INCLUDE_DIR} PARENT_DIRECTORY)








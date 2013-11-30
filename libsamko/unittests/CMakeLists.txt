# build gtest and google mock with same compiler options as tested library
add_subdirectory(gmock)
include_directories ("${PROJECT_SOURCE_DIR}/libsamko/unittests/gmock/include")
link_directories (${SAMKO_BINARY_DIR}/libsamko/unittests/gmock)

include_directories ("${PROJECT_SOURCE_DIR}/libsamko/unittests")

SET(calib2d_test_SOURCES
	tests/calib2d/calibprojectivetest.cpp
   )

SET(serialization_test_SOURCES
	tests/serialization/common.cpp
	tests/serialization/basetest.cpp
	tests/serialization/jsontest.cpp
   )

SET(test_SOURCES 
	${calib2d_test_SOURCES}
	${serialization_test_SOURCES}
   )

add_executable(samko_unittest main.cpp ${test_SOURCES})
target_link_libraries(samko_unittest gmock samko)

install(TARGETS samko_unittest DESTINATION bin)
install(DIRECTORY data DESTINATION bin)


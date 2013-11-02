# build gtest with same compiler options as tested library
add_subdirectory(gtest)
link_directories (${SAMKO_BINARY_DIR}/libsamko/unittests/gtest)

add_subdirectory(data)

SET(calib2d_test_SOURCES
	tests/calib2d/calibprojectivetest.cpp
   )

SET(test_SOURCES 
	${calib2d_test_SOURCES}
   )

add_executable(samko_unittest main.cpp ${test_SOURCES})
target_link_libraries(samko_unittest gtest samko)

find_package( OpenCV REQUIRED )

include_directories ("${PROJECT_SOURCE_DIR}/libsamko/include")

set (calibration2d_SOURCES 
	src/calib2d/coordhomog.cpp
	src/calib2d/calibprojective.cpp
    )

SET (SOURCES 
	${calibration2d_SOURCES}
	src/cvutils.cpp
    )

add_library(samko ${SOURCES})
target_link_libraries(samko 
	opencv_core opencv_imgproc opencv_highgui opencv_calib3d opencv_features2d
  )

add_subdirectory (unittests)

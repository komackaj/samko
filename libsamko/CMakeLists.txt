set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package( OpenCV REQUIRED )
find_package( Jansson REQUIRED )

include_directories ("${PROJECT_SOURCE_DIR}/libsamko/include")

set (calibration2d_SOURCES 
	src/calib2d/coordhomog.cpp
	src/calib2d/calibprojective.cpp
    )

set (serialization_SOURCES
	src/serialization/serializer.cpp
	src/serialization/reader.cpp
	src/serialization/writer.cpp
	src/serialization/memstorage.cpp
	src/serialization/json_common.cpp
	src/serialization/jsonwriter.cpp
	src/serialization/jsonreader.cpp
	src/serialization/adapters/matserializableadapter.cpp
    )

set (ui_SOURCES
	src/ui/uigriddetector.cpp
    )

set (targets_SOURCES
        src/targets/ellipsetargetrefiner.cpp
    )

SET (SOURCES 
	${calibration2d_SOURCES}
	${serialization_SOURCES}
	${ui_SOURCES}
        ${targets_SOURCES}
	src/cvutils.cpp
	src/stringutils.cpp
    )

add_library(samko ${SOURCES})
target_link_libraries(samko 
	opencv_core opencv_imgproc opencv_highgui opencv_calib3d opencv_features2d
	jansson
  )

add_subdirectory (unittests)

install(TARGETS samko DESTINATION bin)

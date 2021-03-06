CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(nnstreamer C CXX)

OPTION(TIZEN "Enable Tizen build mode" OFF)
OPTION(DISABLE_TENSORFLOW_LITE "Disable tensorflow-lite support" OFF)
OPTION(DISABLE_TENSORFLOW "Disable tensorflow support" OFF)
OPTION(INSTALL_EXAMPLE_APP "Install example applications" OFF)

ADD_DEFINITIONS(-DVERSION="0.0.1")

SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(EXEC_PREFIX "${PREFIX}/bin")
SET(INCLUDEDIR "${PREFIX}/include/${PROJECT_NAME}")

IF(LIB_INSTALL_DIR)
ELSE(LIB_INSTALL_DIR)
    SET(LIB_INSTALL_DIR "${PREFIX}/lib")
ENDIF(LIB_INSTALL_DIR)

IF(GST_INSTALL_DIR)
ELSE(GST_INSTALL_DIR)
    SET(GST_INSTALL_DIR "${PREFIX}/lib/gstreamer-1.0")
ENDIF(GST_INSTALL_DIR)

FIND_PACKAGE(PkgConfig REQUIRED)
SET(PKG_MODULES
	gstreamer-1.0
	gstreamer-base-1.0
	gstreamer-controller-1.0
	gstreamer-video-1.0
	gstreamer-audio-1.0
	glib-2.0
)

FIND_LIBRARY(GTEST_LIB gtest)
IF(TIZEN OR GTEST_LIB)
	# Enable dlog of Tizen.
	ADD_DEFINITIONS(-DTIZEN=1)
	SET(PKG_MODULES ${PKG_MODULES} dlog)
	# Use GTEST shared lib
	SET(gtestLink gtest pthread)
	SET(gtestSrc "")
	SET(gtestInc "")
	SET(DISABLE_TENSORFLOW ON)
	MESSAGE("DISABLE_TENSORFLOW : ${DISABLE_TENSORFLOW}")
ELSE(TIZEN OR GTEST_LIB)
	IF (NOT EXISTS /usr/src/gtest/src/gtest-all.cc)
		MESSAGE(FATAL FATAL_ERROR "You need to install libgtest-dev or libgtest.so.")
	ENDIF ()
	SET(gtestLink pthread)
	SET(gtestSrc /usr/src/gtest/src/gtest-all.cc)
	SET(gtestInc /usr/src/gtest)
ENDIF(TIZEN OR GTEST_LIB)

IF (NOT INCLUDE_INSTALL_DIR)
	# We need to define includedir path
	SET (INCLUDE_INSTALL_DIR /usr/include)
	MESSAGE ("Warning: INCLUDE_INSTALL_DIR not defined. Using /usr/include")
ENDIF (NOT INCLUDE_INSTALL_DIR)

pkg_check_modules(pkgs REQUIRED ${PKG_MODULES})

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/include
)
INCLUDE_DIRECTORIES(
	SYSTEM
	${pkgs_INCLUDE_DIRS}
)
LINK_DIRECTORIES(${pkgs_LIBRARY_DIRS})
FOREACH(flag ${pkgs_CFALGS})
	SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

# Gstreamer uses C89
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -Wall -Werror -fPIC -g -std=c89")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CXXFLAGS} -Wall -Werror -fPIC -g -std=c++11")

# Provide common data
ADD_LIBRARY(common STATIC common/tensor_common.c common/tensor_meta.c)
TARGET_LINK_LIBRARIES(common ${pkgs_LIBRARIES})
TARGET_INCLUDE_DIRECTORIES(common PUBLIC ${pkgs_INCLUDE_DIRS})
SET(pkgs_LIBRARIES ${pkgs_LIBRARIES} common)

# Unit test for common
ADD_EXECUTABLE(unittest_common tests/common/unittest_common.cpp ${gtestSrc})
TARGET_INCLUDE_DIRECTORIES(unittest_common PUBLIC ${pkgs_INCLUDE_DIRS} ${gtestInc})
TARGET_LINK_LIBRARIES(unittest_common ${pkgs_LIBRARIES} ${gtestLink})

# Unit test for tensor sink
ADD_EXECUTABLE(unittest_sink tests/nnstreamer_sink/unittest_sink.cpp ${gtestSrc})
TARGET_INCLUDE_DIRECTORIES(unittest_sink PUBLIC ${pkgs_INCLUDE_DIRS} ${gtestInc})
TARGET_LINK_LIBRARIES(unittest_sink ${pkgs_LIBRARIES} ${gtestLink})

ADD_SUBDIRECTORY(gst/tensor_converter)
ADD_SUBDIRECTORY(gst/tensor_filter)
ADD_SUBDIRECTORY(gst/tensor_decoder)
ADD_SUBDIRECTORY(gst/tensor_sink)
ADD_SUBDIRECTORY(gst/tensor_mux)
ADD_SUBDIRECTORY(gst/tensor_demux)
ADD_SUBDIRECTORY(gst/tensor_transform)
ADD_SUBDIRECTORY(gst/tensor_saveload)
ADD_SUBDIRECTORY(nnstreamer_example)
ADD_SUBDIRECTORY(tests/nnstreamer_tensors/tensors_test)
enable_testing()
ADD_SUBDIRECTORY(tests)

CONFIGURE_FILE(nnstreamer.pc.in nnstreamer.pc @ONLY)

# For nnstreamer users (gst app developers using via gstreamer API)
INSTALL(FILES include/tensor_typedef.h
	DESTINATION ${INCLUDE_INSTALL_DIR}/nnstreamer
	)

# For nnstreamer custom filter developers
INSTALL(FILES include/tensor_common.h include/tensor_filter_custom.h include/tensor_meta.h
	DESTINATION ${INCLUDE_INSTALL_DIR}/nnstreamer
	)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/nnstreamer.pc
	DESTINATION ${LIB_INSTALL_DIR}/pkgconfig
	)

# Custom plugins need to use common archive (static lib)
INSTALL(TARGETS common
	RUNTIME DESTINATION ${EXEC_PREFIX}
	LIBRARY DESTINATION ${GST_INSTALL_DIR}
	ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
	)

ADD_LIBRARY(tensor_transform SHARED tensor_transform.c)
ADD_LIBRARY(tensor_transformStatic STATIC tensor_transform.c)

TARGET_LINK_LIBRARIES(tensor_transform ${pkgs_LIBRARIES})
TARGET_INCLUDE_DIRECTORIES(tensor_transform PUBLIC ${pkgs_INCLUDE_DIRS})
TARGET_COMPILE_OPTIONS(tensor_transform PUBLIC ${pkgs_CFLAGS_OTHER})
TARGET_LINK_LIBRARIES(tensor_transformStatic ${pkgs_LIBRARIES})
TARGET_INCLUDE_DIRECTORIES(tensor_transformStatic PUBLIC ${pkgs_INCLUDE_DIRS})
TARGET_COMPILE_OPTIONS(tensor_transformStatic PUBLIC ${pkgs_CFLAGS_OTHER})

INSTALL(TARGETS tensor_transform tensor_transformStatic
	RUNTIME DESTINATION ${EXEC_PREFIX}
	LIBRARY DESTINATION ${GST_INSTALL_DIR}
	ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
	)

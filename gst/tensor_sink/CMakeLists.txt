ADD_LIBRARY(tensor_sink SHARED tensor_sink.c)
ADD_LIBRARY(tensor_sinkStatic STATIC tensor_sink.c)

TARGET_LINK_LIBRARIES(tensor_sink ${pkgs_LIBRARIES})
TARGET_INCLUDE_DIRECTORIES(tensor_sink PUBLIC ${pkgs_INCLUDE_DIRS})
TARGET_COMPILE_OPTIONS(tensor_sink PUBLIC ${pkgs_CFLAGS_OTHER})
TARGET_LINK_LIBRARIES(tensor_sinkStatic ${pkgs_LIBRARIES})
TARGET_INCLUDE_DIRECTORIES(tensor_sinkStatic PUBLIC ${pkgs_INCLUDE_DIRS})
TARGET_COMPILE_OPTIONS(tensor_sinkStatic PUBLIC ${pkgs_CFLAGS_OTHER})

INSTALL(TARGETS tensor_sink tensor_sinkStatic
	RUNTIME DESTINATION ${EXEC_PREFIX}
	LIBRARY DESTINATION ${GST_INSTALL_DIR}
	ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
	)

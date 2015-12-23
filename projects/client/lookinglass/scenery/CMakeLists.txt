
add_project(scenery)

add_library(scenery

	source/lookinglass/scenery/Scene.cpp source/lookinglass/scenery/Scene.h)

include_directories(
	${scenery_includes}
)

target_link_libraries(scenery

  )

add_custom_command(TARGET scenery POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:scenery>/resources)


add_project(scenery)

add_library(scenery

	source/lookinglass/scenery/Scene.cpp
	source/lookinglass/scenery/Scene.h
	source/lookinglass/scenery/elements/Element.h
	source/lookinglass/scenery/elements/Model.cpp
	source/lookinglass/scenery/elements/Model.h
	source/lookinglass/scenery/Spatial_Effect.cpp
	source/lookinglass/scenery/Spatial_Effect.h
		)


require_package(scenery glass)
require_package(scenery shading)

include_directories(
	${scenery_includes}
)

target_link_libraries(scenery

  )

add_custom_command(TARGET scenery POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:scenery>/resources)

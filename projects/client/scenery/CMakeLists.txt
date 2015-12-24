
add_project(scenery)

add_library(scenery

	source/scenery/Scene.cpp
	source/scenery/Scene.h
	source/scenery/elements/Element.h
	source/scenery/elements/Model.cpp
	source/scenery/elements/Model.h
	source/scenery/Spatial_Effect.cpp
	source/scenery/Spatial_Effect.h
	source/scenery/elements/Element.cpp source/scenery/Mesh_Exporter.cpp source/scenery/Mesh_Exporter.h)


require_package(scenery glass)
require_package(scenery shading)

include_directories(
	${scenery_includes}
)

target_link_libraries(scenery

  )

add_custom_command(TARGET scenery POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	resources $<TARGET_FILE_DIR:scenery>/resources)

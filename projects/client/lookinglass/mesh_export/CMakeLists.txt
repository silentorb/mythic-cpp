
add_project(mesh_export)

add_library(mesh_export

	source/lookinglass/mesh_export.h source/lookinglass/mesh_export.cpp)

require_package(mesh_export glass)
require_package(mesh_export sculptor)

include_directories(
	${mesh_export_includes}
)

target_link_libraries(mesh_export

  )

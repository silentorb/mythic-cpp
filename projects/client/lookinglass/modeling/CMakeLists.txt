
add_project(modeling)

create_library(modeling
	source/lookinglass/modeling/mesh_export.h
	source/lookinglass/modeling/mesh_export.cpp
	source/lookinglass/modeling/Textured_Vertex.h
	source/lookinglass/modeling/Vertex_Schema.cpp
	source/lookinglass/modeling/Vertex_Schema.h
	source/lookinglass/modeling/Vertex_Attribute.cpp
	source/lookinglass/modeling/Vertex_Attribute.h
	source/lookinglass/modeling/Mesh_Data.h
	source/lookinglass/modeling/Mesh_Data.cpp
)

require_package(modeling sculptor)
require_package(modeling glow)
include_directories(

)

target_link_libraries(modeling

  )

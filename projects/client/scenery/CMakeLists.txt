
add_project(scenery)

create_library(scenery

	source/scenery/Scene.cpp
	source/scenery/Scene.h
	source/scenery/Scene_Manager.cpp
	source/scenery/Scene_Manager.h
	source/scenery/elements/Element.h
	source/scenery/elements/Model.cpp
	source/scenery/elements/Model.h
	source/scenery/Spatial_Effect.cpp
	source/scenery/Spatial_Effect.h
	source/scenery/elements/Element.cpp)

require_package(scenery glass)
require_package(scenery shading)
require_package(scenery modeling)
require_package(scenery glow)

target_link_libraries(scenery

  )

add_resources(resources)

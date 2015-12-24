
add_project(mythic)

add_library(mythic

	source/mythic/Mythic_Engine.cpp source/mythic/Mythic_Engine.h source/mythic/Myth.cpp source/mythic/Myth.h source/mythic/Mythic_Renderer.cpp source/mythic/Mythic_Renderer.h)

require_package(mythic quartz)
require_package(mythic client)
require_package(mythic glass)
require_package(mythic lookinglass)

include_directories(
	${mythic_includes}
)

target_link_libraries(mythic

  )


add_project(mythic)

add_library(mythic

	source/mythic/Mythic_Engine.cpp source/mythic/Mythic_Engine.h)

require_package(mythic quartz)
require_package(mythic client)


include_directories(
	${mythic_includes}
)

target_link_libraries(mythic

  )

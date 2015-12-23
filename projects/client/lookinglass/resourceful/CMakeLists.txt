
add_project(resourceful)

add_library(resourceful

	source/lookinglass/resourceful/Resource_Manager.cpp source/lookinglass/resourceful/Resource_Manager.h)

include_directories(
	${resourceful_includes}
)

target_link_libraries(resourceful

  )

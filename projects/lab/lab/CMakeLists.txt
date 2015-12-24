
add_project(lab)

add_library(lab

	source/laboratory/Lab.cpp source/laboratory/Lab.h)

require_package(lab mythic)

include_directories(
	${lab_includes}
)

target_link_libraries(lab

  )

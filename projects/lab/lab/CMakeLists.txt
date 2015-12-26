
add_project(lab)

create_library(lab

	source/laboratory/Lab.cpp
	source/laboratory/Lab.h
	source/laboratory/display/Lab_Renderer.cpp
	source/laboratory/display/Lab_Renderer.h
	)

require_package(lab mythic)
require_package(lab architecture_lab)
require_package(lab glass)

include_directories(
	${lab_includes}
)

target_link_libraries(lab

  )

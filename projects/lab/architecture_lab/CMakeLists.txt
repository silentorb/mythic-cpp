
add_project(architecture_lab)

create_library(architecture_lab

	source/laboratory/Architecture_Lab.cpp
	source/laboratory/Architecture_Lab.h
	source/laboratory/display/Freeform_Camera.cpp
	source/laboratory/display/Freeform_Camera.h

	)

require_package(architecture_lab glass)
require_package(architecture_lab mythic)
require_package(architecture_lab scenery)
require_package(architecture_lab sculptor)
require_package(architecture_lab shading)
require_package(architecture_lab modeling)

include_directories(
	${architecture_lab_includes}
)

target_link_libraries(architecture_lab

  )

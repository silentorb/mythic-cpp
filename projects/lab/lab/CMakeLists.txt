
add_project(lab)

add_library(lab

	source/laboratory/Lab.cpp
	source/laboratory/Lab.h
	source/laboratory/display/Freeform_Camera.cpp
	source/laboratory/display/Freeform_Camera.h
	source/laboratory/display/Lab_Renderer.cpp
	source/laboratory/display/Lab_Renderer.h)

require_package(lab mythic)
require_package(lab glass)

include_directories(
	${lab_includes}
)

target_link_libraries(lab

  )

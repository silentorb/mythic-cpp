
add_project(drawing)

create_library(drawing

	source/lookinglass/drawing/Draw.cpp source/lookinglass/drawing/Draw.h)

include_directories(
	${drawing_includes}
)

target_link_libraries(drawing

  )

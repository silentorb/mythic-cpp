
add_project(typography)

create_library(typography
	source/lookinglass/typography/Font_Manager.cpp
	source/lookinglass/typography/Font_Manager.h
)

include_directories(
	${typography_includes}
)
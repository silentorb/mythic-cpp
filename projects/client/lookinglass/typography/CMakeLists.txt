
add_project(typography)

add_library(typography
	source/lookinglass/typography/Font_Manager.cpp
	source/lookinglass/typography/Font_Manager.h
)

include_directories(
	${typography_includes}
)
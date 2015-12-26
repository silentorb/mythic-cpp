
add_project(through)

include_directories(
	${through_includes}
	${shading_includes}
)

create_library(through

	source/lookinglass/through/Mist.h
	source/lookinglass/through/Ancient_Mist.cpp
	source/lookinglass/through/Ancient_Mist.h
	source/lookinglass/through/Buffer_Mist.cpp
	source/lookinglass/through/Mist_Maker.cpp
	source/lookinglass/through/Mister_D.cpp)

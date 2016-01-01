
#add_project(through)

#include_directories(
#	${through_includes}
#	${shading_includes}
#)

create_library(through

#	source/lookinglass/through/Mist.h
#	source/lookinglass/through/create_mist.h
#	source/lookinglass/through/Ancient_Mist.cpp
#	source/lookinglass/through/Ancient_Mist.h
#	source/lookinglass/through/Buffer_Mist.cpp
#	source/lookinglass/through/Buffer_Mist.h
#	source/lookinglass/through/Mister_D.cpp
#	source/lookinglass/through/Data_Buffer.h
#	source/lookinglass/through/Data_Buffer.cpp
	)

find_package(math)
require_package(through glow)
require_package(through shading)
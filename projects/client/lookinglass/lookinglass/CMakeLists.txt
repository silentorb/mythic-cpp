
add_project(lookinglass)

create_library(lookinglass
  source/lookinglass/House.cpp
	source/lookinglass/House.h
	source/lookinglass/Platform_Factory.h
	)

include_directories(
	${lookinglass_includes}
  ${MYTHIC_EXTERNAL}/SDL2-2.0.3/include
)

find_package(math)
find_package(vectoring)
require_package(lookinglass glass)
require_package(lookinglass glow)
require_package(lookinglass shading)
require_package(lookinglass perspective)
require_package(lookinglass through)

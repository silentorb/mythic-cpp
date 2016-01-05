
add_project(lookinglass)

create_library(lookinglass)

include_directories(
	${lookinglass_includes}
  ${MYTHIC_EXTERNAL}/SDL2-2.0.3/include
)

find_package(math)
find_package(vectoring)
require(glass)
require(glow)
require(shading)
require(perspective)
require(through)

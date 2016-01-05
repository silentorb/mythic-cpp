
add_project(glass)

create_library(glass)

require(glow)
require(shading)
require(modeling)
require(perspective)

include_directories(
	${glass_includes}
)

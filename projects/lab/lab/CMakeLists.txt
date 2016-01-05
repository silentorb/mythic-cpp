
add_project(lab)

create_library(lab)

require(mythic)
require(architecture_lab)
require(glass)

include_directories(
	${lab_includes}
)


add_project(architect)

add_library(architect

	source/architecture/Architect.cpp source/architecture/Architect.h)

find_package(math)
require_package(architect sculptor)

include_directories(
	${architect_includes}
)

target_link_libraries(architect

  )

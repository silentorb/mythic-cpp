
#add_project(through)

#include_directories(
#	${through_includes}
#	${shading_includes}
#)

create_library(through)

find_package(math)
require(glow)
require(shading)
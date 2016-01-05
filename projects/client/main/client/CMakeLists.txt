
add_project(client)

create_library(client)

require(lookinglass)
require(haft)

include_directories(
	${client_includes}
)

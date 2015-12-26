
add_project(client)

create_library(client

	source/clienting/Client.cpp source/clienting/Client.h)

require_package(client lookinglass)

include_directories(
	${client_includes}
)

target_link_libraries(client

  )

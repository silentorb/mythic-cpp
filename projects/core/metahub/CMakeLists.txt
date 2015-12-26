
add_project(metahub)

create_library(metahub

	source/metahub/metahub.c source/metahub/metahub.h source/metahub/hub.c source/metahub/hub.h source/metahub/common.h source/metahub/node.c source/metahub/node.h source/metahub/list.cpp source/metahub/list.h)

include_directories(
	${metahub_includes}
)

target_link_libraries(metahub

  )

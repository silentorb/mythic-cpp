
add_project(quartz)

create_library(quartz
	source/timing/Quartz.cpp
	source/timing/Quartz.h
)

include_directories(
	${quartz_includes}
)

target_link_libraries(quartz

  )

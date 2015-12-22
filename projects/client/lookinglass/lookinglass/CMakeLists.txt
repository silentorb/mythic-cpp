
add_project(lookinglass)

add_library(lookinglass
	source/lookinglass/Glass.cpp
	source/lookinglass/Glass.h
  source/lookinglass/House.cpp
	source/lookinglass/House.h)

include_directories(
	${lookinglass_includes}
  ${MYTHIC_EXTERNAL}/SDL2-2.0.3/include
	${MYTHIC_EXTERNAL}/glm
)

find_package(frame)
require_package(lookinglass glow)

add_custom_command(TARGET lookinglass POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${MYTHIC_EXTERNAL}/SDL2-2.0.3/bin/SDL2.dll $<TARGET_FILE_DIR:lookinglass
  )


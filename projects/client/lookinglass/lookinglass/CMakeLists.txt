
add_project(lookinglass)

add_library(lookinglass
  source/lookinglass/House.cpp
	source/lookinglass/House.h)

include_directories(
	${lookinglass_includes}
  ${MYTHIC_EXTERNAL}/SDL2-2.0.3/include
)

find_package(math)
find_package(vectoring)
require_package(lookinglass glass)
require_package(lookinglass glow)

add_custom_command(TARGET lookinglass POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${MYTHIC_EXTERNAL}/SDL2-2.0.3/bin/SDL2.dll $<TARGET_FILE_DIR:lookinglass
  )


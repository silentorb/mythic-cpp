cmake_minimum_required(VERSION 3.3)

project(lookinglass)

set(lookinglass_DIR ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)

include(lookinglass-config.cmake)

add_library(lookinglass SHARED
	include/lookinglass/Glass.cpp
	include/lookinglass/Glass.h
)

include_directories(
	${lookinglass_includes}
  ${MYTHIC_EXTERNAL}/SDL2-2.0.3/include
	${MYTHIC_EXTERNAL}/glm
)

#message(WARNING ${MYTHIC_EXTERNAL_INCLUDE}/SDL2/include)
#message(WARNING ${MYTHIC_EXTERNAL}/SDL2-2.0.3/lib/libSDL2.dll.a)

#message("CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(lookinglass
  ${MYTHIC_EXTERNAL}/SDL2-2.0.3/lib/libSDL2.dll.a
#	"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib/x64/OpenGL32.Lib"
#	${CMAKE_BINARY_DIR}/external/freetype-2.6/Debug/freetype.lib
)

add_custom_command(TARGET lookinglass POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${MYTHIC_EXTERNAL}/SDL2-2.0.3/bin/SDL2.dll $<TARGET_FILE_DIR:lookinglass
  )

#add_custom_command(TARGET lookinglass POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_directory
#	${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:lookinglass>/resources)
#add_custom_command(TARGET lookinglass POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_directory
#	${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:lookinglass>/resources)
#
#message("$<TARGET_FILE_DIR:lookinglass>" $<TARGET_FILE_DIR:lookinglass>)

cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package (lookinglass)
find_package (frame)

project(workshop)

add_executable(workshop
	source/Workshop.cpp
)

include_directories(
	${CMAKE_CURRENT_LIST_DIR}/source
  ${lookinglass_includes}
	${frame_includes}
)
#message(WARNING ${lookinglass_libs})

target_link_libraries(workshop
  $<TARGET_LINKER_FILE:lookinglass>
	$<TARGET_LINKER_FILE:frame>
  )

add_custom_command(TARGET workshop POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${MYTHIC_EXTERNAL}/bin $<TARGET_FILE_DIR:workshop>
  )
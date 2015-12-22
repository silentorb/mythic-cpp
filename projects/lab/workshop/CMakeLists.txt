cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(workshop)

add_executable(workshop
  source/Workshop.cpp
  )

find_package(lookinglass)
require_package(workshop desktop)

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/source
    )

target_link_libraries(workshop
  )

add_custom_command(TARGET workshop POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${MYTHIC_EXTERNAL}/bin $<TARGET_FILE_DIR:workshop>
  )
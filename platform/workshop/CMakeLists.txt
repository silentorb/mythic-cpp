cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(workshop)

add_executable(workshop
  source/Workshop.cpp
  source/Workshop.h
  )

include_directories(${CMAKE_TOOLS}/include)

require_package(workshop desktop)
require_package(workshop mythic)
require_package(workshop lab)

#if (${MINGW})
#  add_custom_command(TARGET workshop POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory ${MYTHIC_EXTERNAL}/mingw/bin $<TARGET_FILE_DIR:workshop>
#    )
#endif ()
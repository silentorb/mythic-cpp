cmake_minimum_required(VERSION 3.3)

include(cmake-utility/print-info.cmake)
include(cmake-utility/project.cmake)

set(MYTHIC_EXTERNAL ${CMAKE_SOURCE_DIR}/external/mingw)
set(GLM_INCLUDES ${CMAKE_SOURCE_DIR}/external/glm)

set(BUILD_SHARED_LIBS true)
#start sub-projects

add_subdirectory(projects/misc/math)
include(projects/client/lookinglass/lookinglass.cmake)
add_subdirectory(projects/generation/sculptor)
#end sub-projects

add_subdirectory(platform/desktop)
add_subdirectory(platform/workshop)

#add_dependencies(workshop
#  lookinglass
#  desktop
#  )

#add_dependencies(lookinglass
#  glow
#  shading
#  through
#  perspective
#  scenery
#  )
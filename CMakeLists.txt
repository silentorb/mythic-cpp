cmake_minimum_required(VERSION 3.3)

include(cmake-utility/print-info.cmake)
include(cmake-utility/project.cmake)

set(MYTHIC_EXTERNAL ${CMAKE_SOURCE_DIR}/external/mingw)
set(GLM_INCLUDES ${CMAKE_SOURCE_DIR}/external/glm)

set(BUILD_SHARED_LIBS true)

#add_subdirectory(projects/core/metahub)

#start sub-projects

add_subdirectory(projects/misc/quartz)
add_subdirectory(projects/misc/math)
add_subdirectory(projects/misc/vectoring)
add_subdirectory(projects/generation/sculptor)

include(projects/client/lookinglass/lookinglass.cmake)
add_subdirectory(projects/client/scenery)
add_subdirectory(projects/client/main/client)
add_subdirectory(projects/generation/architect)
#end sub-projects

add_subdirectory(projects/core/mythic)
include(projects/lab/lab.cmake)

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
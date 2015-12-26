cmake_minimum_required(VERSION 3.3)

if (${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
  set(iOS true)
  add_definitions(-DIOS=1)
  message(STATUS hello)
  #include(toolchains/ios.cmake)
  set(BUILD_SHARED_LIBS OFF)
  message(STATUS bye)

else

endif()

set(GLM_INCLUDES ${CMAKE_SOURCE_DIR}/external/glm)

include(cmake-utility/print-info.cmake)
include(cmake-utility/project.cmake)

set(MYTHIC_EXTERNAL ${CMAKE_SOURCE_DIR}/external/mingw)

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

if (NOT ${iOS})
  add_subdirectory(platform/desktop)
  add_subdirectory(platform/workshop)
endif()

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

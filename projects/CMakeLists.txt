cmake_minimum_required(VERSION 3.3)

set(BUILD_SHARED_LIBS true)

#start sub-projects

add_subdirectory(client/lookinglass/lookinglass)
add_subdirectory(client/lookinglass/typography)
add_subdirectory(client/lookinglass/frame)
#end sub-projects

add_subdirectory(lab/workshop)

add_dependencies(workshop
  lookinglass
  )

add_dependencies(lookinglass
  frame
  )
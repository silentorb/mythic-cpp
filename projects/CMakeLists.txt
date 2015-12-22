set(BUILD_SHARED_LIBS true)

#start sub-projects

add_subdirectory(client/lookinglass/glow)
add_subdirectory(client/lookinglass/lookinglass)
add_subdirectory(client/lookinglass/typography)
add_subdirectory(client/lookinglass/shading)
add_subdirectory(client/lookinglass/frame)
add_subdirectory(client/lookinglass/through)
add_subdirectory(client/lookinglass/perspective)
#end sub-projects

add_subdirectory(lab/workshop)

add_dependencies(workshop
  lookinglass
  )

add_dependencies(lookinglass
  glow
  shading
  through
  perspective
  frame
  )
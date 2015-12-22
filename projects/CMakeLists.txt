set(BUILD_SHARED_LIBS true)

#start sub-projects

add_subdirectory(client/lookinglass/glow)
add_subdirectory(client/lookinglass/typography)
add_subdirectory(client/lookinglass/shading)
add_subdirectory(client/lookinglass/frame)
add_subdirectory(client/lookinglass/through)
add_subdirectory(client/lookinglass/perspective)
add_subdirectory(client/lookinglass/lookinglass)
add_subdirectory(platform/desktop)
#end sub-projects

add_subdirectory(platform/workshop)

add_dependencies(workshop
  lookinglass
  desktop
  )

add_dependencies(lookinglass
  glow
  shading
  through
  perspective
  )
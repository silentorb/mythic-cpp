# Lookinglass Projects
macro(add name)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/${name})
endmacro(add)

add(glow)
add(typography)
add(shading)
add(frame)
add(through)
add(perspective)
add(scenery)
add(lookinglass)
add(drawing)
add(resourceful)
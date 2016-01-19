
create_library(typography)

require(resourceful shading glow)

add_resources(resources)

if (MSVC)

elseif (MINGW)
  target_link_libraries(desktop ${MYTHIC_EXTERNAL}/freetype/mingw64/libfreetype.a)
endif ()


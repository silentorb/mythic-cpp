
create_library(typography)

require(resourceful shading glow textual texturing)

if(NOT IOS)
  link_external(zlib)
endif()

link_external_static(freetype)

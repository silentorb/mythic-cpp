
create_library(typography)

require(resourceful shading glow textual texturing perspective)

if(NOT IOS)
#  link_external(zlib)
endif()

if (MINGW)
  link_external(freetype)
else()
  link_external_static(freetype)
endif()
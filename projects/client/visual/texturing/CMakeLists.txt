
create_library(texturing)

require(glow resourceful shading math)

add_resources(resources)

if (NOT IOS)
  link_external(libpng)
  link_external(zlib)
endif ()

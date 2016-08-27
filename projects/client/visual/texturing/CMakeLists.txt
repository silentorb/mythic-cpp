
create_library(texturing)

require(glow resourceful shading)

add_resources(resources)

if (NOT IOS)
  if (ANDROID)
    link_external(libpng)
  else ()
    link_external(libpng libpng16)
  endif ()
  link_external(zlib)
endif ()

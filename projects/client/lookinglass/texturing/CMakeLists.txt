
create_library(texturing)

require(glow resourceful shading)

add_resources(resources)

include_directories(
  ${MYTHIC_DEPENDENCIES}/libpng/include
)

if(NOT IOS)
  link_external(libpng libpng16)
  link_external(zlib)
endif()


create_library(svg)

require(shading drawing texturing)

include_directories(
  ${MYTHIC_DEPENDENCIES}/pugixml/include
)

link_external(pugixml)
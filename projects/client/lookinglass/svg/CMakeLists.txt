
create_library(svg)

require(shading drawing texturing)

include_directories(
#  ${MYTHIC_DEPENDENCIES}/pugixml/include
  ${MYTHIC_DEPENDENCIES}/nanosvg/src
)

#link_external(pugixml)
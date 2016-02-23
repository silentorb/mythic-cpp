
create_library(archaeology)

include_directories(${MYTHIC_DEPENDENCIES}/pugixml/include)

require(sculptor textual)

link_external_static(pugixml)

find_package(math)

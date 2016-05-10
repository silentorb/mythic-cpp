
create_library(vineyard)
require(promising songbird)
link_external_static(sqlite)
add_definitions(-DVINEYARD_LIB)
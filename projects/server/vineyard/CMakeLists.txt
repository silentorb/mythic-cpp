
create_library(vineyard)
require(promising songbird logger)
link_external_static(sqlite)
add_definitions(-DVINEYARD_LIB)
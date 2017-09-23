
create_library(archaeology)

require(sculptor textual math)
if (ANDROID)
  link_external_static(pugixml)
else ()
  link_external(pugixml)
endif ()

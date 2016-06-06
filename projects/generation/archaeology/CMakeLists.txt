
create_library(archaeology)

#include_directories(${MYTHIC_DEPENDENCIES}/pugixml/include)

require(sculptor textual)
if (ANDROID)
  link_external_static(pugixml)
else ()
  link_external(pugixml)
endif ()
find_package(math)

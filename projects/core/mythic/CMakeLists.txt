
add_project(mythic)

create_library(mythic)

find_package(vectoring)
require(quartz)
require(client)
require(glass)
require(lookinglass)

include_directories(
  ${mythic_includes}
)

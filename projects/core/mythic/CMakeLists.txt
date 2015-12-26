
add_project(mythic)

create_library(mythic
  ${platform_sources}
  source/mythic/Mythic_Engine.cpp
  source/mythic/Mythic_Engine.h
  source/mythic/Myth.cpp
  source/mythic/Myth.h
  source/mythic/Mythic_Renderer.cpp
  source/mythic/Mythic_Renderer.h
  source/mythic/Myth_Info.h
  source/mythic/Simple_Myth_Info.cpp
  source/mythic/Simple_Myth_Info.h)

find_package(vectoring)
require_package(mythic quartz)
require_package(mythic client)
require_package(mythic glass)
require_package(mythic lookinglass)

include_directories(
  ${mythic_includes}
)

target_link_libraries(mythic

  )

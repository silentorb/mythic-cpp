
add_project(desktop)

add_library(desktop
  source/desktop/Desktop_Frame.cpp
  source/desktop/Desktop_Frame.h
  source/desktop/Desktop_Shader_Loader.cpp source/desktop/Desktop_Shader_Loader.h)

require_package(desktop shading)
require_package(desktop glow)

include_directories(
  ${desktop_includes}
  ${MYTHIC_EXTERNAL}/SDL2-2.0.3/include
)

target_link_libraries(desktop
  ${MYTHIC_EXTERNAL}/SDL2-2.0.3/lib/libSDL2.dll.a
  )

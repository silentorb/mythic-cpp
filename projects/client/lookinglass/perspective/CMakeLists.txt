
add_project(perspective)

include_directories(
  ${MYTHIC_EXTERNAL}/glm
)

add_library(perspective
  source/lookinglass/perspective/Viewport.cpp
  source/lookinglass/perspective/Viewport.h
  source/lookinglass/perspective/Viewport_Data.h
  source/lookinglass/perspective/Camera.cpp
  source/lookinglass/perspective/Camera.h)

require_package(perspective shading)
require_package(perspective glow)

target_link_libraries(perspective
  )

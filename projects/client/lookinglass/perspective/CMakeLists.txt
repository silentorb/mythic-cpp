
add_project(perspective)

include_directories(
  ${perspective_includes}
  ${through_includes}
  ${shading_includes}
  ${MYTHIC_EXTERNAL}/glm
)

add_library(perspective

  source/lookinglass/perspective/Viewport.cpp
  source/lookinglass/perspective/Viewport.h
  source/lookinglass/perspective/Viewport_Data.h source/lookinglass/perspective/Camera.cpp source/lookinglass/perspective/Camera.h)

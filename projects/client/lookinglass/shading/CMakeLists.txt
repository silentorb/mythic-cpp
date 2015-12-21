
add_project(shading)

include_directories(
  ${shading_includes}
)

add_library(shading

  source/lookinglass/shading/Program.cpp
  source/lookinglass/shading/Program.h
  source/lookinglass/shading/Shader.cpp
  source/lookinglass/shading/Shader.h
  source/lookinglass/shading/Effect.h)
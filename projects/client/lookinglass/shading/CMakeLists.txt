
add_project(shading)

add_library(shading

  source/lookinglass/shading/Program.cpp
  source/lookinglass/shading/Program.h
  source/lookinglass/shading/Shader.cpp
  source/lookinglass/shading/Shader.h
  source/lookinglass/shading/effects/Effect.h
  source/lookinglass/shading/Shader_Manager.cpp
  source/lookinglass/shading/Shader_Manager.h
  source/lookinglass/shading/Texture_Manager.cpp
  source/lookinglass/shading/Texture_Manager.h
  source/lookinglass/shading/Shader_Manager.cpp
  source/lookinglass/shading/Shader_Manager.h
  source/lookinglass/shading/Ancient_Shader_Manager.cpp
  source/lookinglass/shading/Ancient_Shader_Manager.h
    source/lookinglass/shading/Shader_Loader.h)

include_directories(
  ${shading_includes}
)

require_package(shading glow)

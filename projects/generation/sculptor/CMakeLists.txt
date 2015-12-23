
add_project(sculptor)

add_library(sculptor

  source/sculptor/geometry/Mesh.cpp
  source/sculptor/geometry/Mesh.h
  source/sculptor/geometry.h
  source/sculptor/geometry/Vertex.cpp
  source/sculptor/geometry/Vertex.h
  source/sculptor/geometry/Edge.cpp
  source/sculptor/geometry/Edge.h
  source/sculptor/geometry/Polygon.cpp
  source/sculptor/geometry/Polygon.h
  source/sculptor/geometry/declarations.h
  source/sculptor/operations/extrude.cpp
  source/sculptor/operations/extrude.h source/sculptor/create.cpp source/sculptor/create.h)

include_directories(
  ${sculptor_includes}
)
find_package(math)
find_package(vectoring)

target_link_libraries(sculptor

  )

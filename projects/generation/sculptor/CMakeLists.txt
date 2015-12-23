
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
  source/sculptor/geometry/declarations.h ../../misc/vectoring/source/vectoring/utility.h source/sculptor/operations/Extrude.cpp source/sculptor/operations/Extrude.h)

include_directories(
  ${sculptor_includes}
)
find_package(math)
find_package(vectoring)

target_link_libraries(sculptor

  )


macro(add_project project_name)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

  project(${project_name})

  set(${project_name}_DIR ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)

  include(${project_name}-config.cmake)

endmacro(add_project)
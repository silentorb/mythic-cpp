
macro(add_project project_name)

  project(${project_name})

  set(${project_name}_DIR ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)

  include(${project_name}-config.cmake)

endmacro(add_project)
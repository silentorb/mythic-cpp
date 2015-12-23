
macro(add_project project_name)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

  project(${project_name})

  set(${project_name}_DIR ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)

  include(${project_name}-config.cmake)

endmacro(add_project)

macro(require_package project_name library_name)
  find_package(${library_name} REQUIRED)

  target_link_libraries(${project_name}
    $<TARGET_LINKER_FILE:${library_name}>
    )

  add_dependencies(${project_name}
    ${library_name}
    )

endmacro(require_package)
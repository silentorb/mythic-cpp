set(CMAKE_UTILITY ${CMAKE_CURRENT_LIST_DIR})

macro(create_library target)

  if ("${ARGN}" STREQUAL "")
    #    message("No sources for ${target}")
    file(GLOB_RECURSE SOURCES source/*.cpp)
    file(GLOB_RECURSE HEADERS source/*.h)
    add_library(${target} ${SOURCES} ${HEADERS})
  else ()
    add_library(${target} ${ARGN})
  endif ()

  string(LENGTH "${CMAKE_SOURCE_DIR}" string_length)
  math(EXPR string_length "${string_length} + 1")
  string(SUBSTRING ${CMAKE_CURRENT_SOURCE_DIR} ${string_length} -1 current_path)
  get_filename_component(current_path ${current_path} DIRECTORY)
  set_target_properties(${target} PROPERTIES FOLDER ${current_path})
  #      message( "${current_path} ${temp}")

  if (IOS)
    set_xcode_property(${target} IPHONEOS_DEPLOYMENT_TARGET "8.0")
  else ()
    include_directories(${CMAKE_UTILITY}/include) # for dllexport
    set_target_properties(${target} PROPERTIES DEFINE_SYMBOL "EXPORTING_DLL")
  endif (IOS)

endmacro(create_library)


if (IOS)

  macro(add_project project_name)
    message(STATUS "ios ${project_name}")
    #include(${CMAKE_SOURCE_DIR}/toolchains/ios.cmake)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    project(${project_name})

    set(${project_name}_DIR ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)

    include(${project_name}-config.cmake)
  endmacro(add_project)

  #  macro(create_library target)
  #    add_library(${target} ${ARGN})
  #    set_xcode_property(${target} IPHONEOS_DEPLOYMENT_TARGET "8.0")
  #  endmacro(create_library)

  macro(require_package project_name library_name)
    find_package(${library_name} REQUIRED)

    target_link_libraries(${project_name}
      $<TARGET_FILE:${library_name}>
      )

    add_dependencies(${project_name}
      ${library_name}
      )

  endmacro(require_package)

else ()

  macro(add_project project_name)
    if (${MINGW})
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif ()

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

endif ()


macro(add name)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/${name})
endmacro(add)

set(CMAKE_UTILITY ${CMAKE_CURRENT_LIST_DIR})

if (iOS)

  macro(add_project project_name)
    message(STATUS "ios ${project_name}")
    #include(${CMAKE_SOURCE_DIR}/toolchains/ios.cmake)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    project(${project_name})

    set(${project_name}_DIR ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)

    include(${project_name}-config.cmake)
  endmacro(add_project)

  macro(create_library target)
    add_library(${target} STATIC ${ARGN})
    set_xcode_property(${target} IPHONEOS_DEPLOYMENT_TARGET "8.0")
  endmacro(create_library)

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

  macro(create_library target)
    add_library(${target} ${ARGN})
    include_directories(${CMAKE_UTILITY}/include) # for dllexport
      set_target_properties(${target} PROPERTIES DEFINE_SYMBOL "EXPORTING_DLL")
#      add_definitions(-DMYTHIC_EXPORT)
  endmacro(create_library)

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

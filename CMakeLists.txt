cmake_minimum_required(VERSION 3.3)
enable_language(CXX) # SINCE Compiler/Platform variables do not normally exist before a project command in CMake.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (NOT MINGW)
  project(mythical)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

if (${IOS})
  add_definitions(-DIOS=1)
  set(BUILD_SHARED_LIBS OFF)
else ()
  set(BUILD_SHARED_LIBS true)
endif ()

include(cmake-tools/cmake-tools.cmake)

#print_info(STATUS)

set(MYTHIC_EXTERNAL ${CMAKE_SOURCE_DIR}/external)

if (MINGW)
  set(SDL_BIN ${MYTHIC_EXTERNAL}/SDL2-2.0.3/i686-w64-mingw32/bin/SDL2.dll)
  set(SDL_LIB ${MYTHIC_EXTERNAL}/SDL2-2.0.3/i686-w64-mingw32/lib/libSDL2.dll.a)
  set(OPENGL_LIB -lglu32 -lopengl32)
elseif (MSVC)
  set(SDL_BIN ${MYTHIC_EXTERNAL}/SDL2-2.0.3/lib/x86/SDL2.dll)
  set(SDL_LIB ${MYTHIC_EXTERNAL}/SDL2-2.0.3/lib/x86/SDL2.lib)
  set(OPENGL_LIB opengl32.lib)
endif ()

add_subdirectory(projects/core/metahub)

#start sub-projects

add_subdirectory(projects/misc/quartz)
add_subdirectory(projects/misc/math)
add_subdirectory(projects/misc/vectoring)
add_subdirectory(projects/misc/textual)
add_subdirectory(external/boost_regex)

add_subdirectory(projects/generation/sculptor)

include(projects/client/lookinglass/lookinglass.cmake)
add_subdirectory(projects/client/scenery)
add_subdirectory(projects/client/haft)
add_subdirectory(projects/client/main/client)
add_subdirectory(projects/generation/architect)
#end sub-projects

add_subdirectory(projects/core/mythic)
include(projects/lab/lab.cmake)

if (ANDROID)
  add_subdirectory(platform/mythic_android)
  add_subdirectory(platform/workshop_android)

elseif (IOS)
  add_subdirectory(platform/mythic_ios)

else ()
  add_subdirectory(platform/desktop)
  add_subdirectory(platform/workshop)

endif ()

finish_mythic()
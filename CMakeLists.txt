cmake_minimum_required(VERSION 3.3)
enable_language(CXX) # SINCE Compiler/Platform variables do not normally exist before a project command in CMake.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(cmake-tools/scripts/generator-key.cmake)

set(LOCAL_HEADER 1)
include(local-config.cmake OPTIONAL)

if (NOT MINGW)
  project(mythical)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

include(cmake-tools/cmake-tools.cmake)

#print_info(STATUS)

set(MYTHIC_EXTERNAL ${CMAKE_SOURCE_DIR}/external)
set(MYTHIC_DEPENDENCIES ${CMAKE_SOURCE_DIR}/dependencies/${GENERATOR_KEY})

if (MINGW)
  set(SDL_BIN ${MYTHIC_DEPENDENCIES}/sdl2/bin/SDL2.dll)
  set(SDL_LIB ${MYTHIC_DEPENDENCIES}/sdl2/lib/libSDL2.dll.a)
  set(OPENGL_LIB -lglu32 -lopengl32)
elseif (MSVC)
  set(SDL_BIN ${MYTHIC_DEPENDENCIES}/sdl2/lib/SDL2.dll)
  set(SDL_LIB ${MYTHIC_DEPENDENCIES}/sdl2/lib/SDL2.lib)
  set(OPENGL_LIB opengl32.lib)
endif ()

#add_subdirectory(projects/core/metahub)

#start sub-projects

add_subdirectory(projects/misc/logger)
add_subdirectory(projects/misc/quartz)
add_subdirectory(projects/misc/math)
add_subdirectory(projects/misc/vectoring)
add_subdirectory(projects/misc/textual)
add_subdirectory(projects/misc/spatial)
add_subdirectory(projects/misc/random)
add_subdirectory(projects/misc/promising)
add_subdirectory(projects/misc/breeze)
add_subdirectory(projects/misc/songbird)
add_subdirectory(external/boost_regex)

add_subdirectory(projects/generation/sculptor)
add_subdirectory(projects/generation/archaeology)
add_subdirectory(projects/client/resourceful)

include(projects/client/lookinglass/lookinglass.cmake)
add_subdirectory(projects/server/substance)
add_subdirectory(projects/client/scenery)
add_subdirectory(projects/client/haft)
add_subdirectory(projects/client/client)
add_subdirectory(projects/generation/architect)
#end sub-projects

add_subdirectory(projects/core/mythic)

add_subdirectory(projects/client/bloom)
add_subdirectory(projects/client/bloom_scenery)

include(projects/lab/lab.cmake)

if (ANDROID)
  add_subdirectory(platform/mythic_android)
  add_subdirectory(platform/workshop_android)

elseif (IOS)
  add_subdirectory(platform/mythic_ios)

else ()
  add_subdirectory(platform/mythic_desktop)
  add_subdirectory(platform/workshop)

endif ()

unset(LOCAL_HEADER)
set(LOCAL_FOOTER 1)
include(local-config.cmake OPTIONAL)

finish_mythic()

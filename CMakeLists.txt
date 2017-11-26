cmake_minimum_required(VERSION 3.3)

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

if (NOT ANDROID)
  enable_language(CXX) # SINCE Compiler/Platform variables do not normally exist before a project command in CMake.
endif ()
SET(CMAKE_EXE_LINKER_FLAGS "-static")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(../../../../cmake-tools/scripts/generator-key.cmake)

set(LOCAL_HEADER 1)
include(local-config.cmake OPTIONAL)

if (NOT MINGW)
  project(mythical)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

macro(on_create_target)
  include_directories(${CMAKE_SOURCE_DIR}/projects/misc/commoner/source) # for dllexport
  if (COMMAND on_create_target_local)
    on_create_target_local()
  endif ()
endmacro()

macro(on_enumerate_target_sources)
  #  message("${CMAKE_CURRENT_SOURCE_DIR}/generated")
  if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/generated)
    #    message("generated")
    file(GLOB_RECURSE CURRENT_SOURCES generated/*.cpp)
    if (CURRENT_SOURCES)
      list(APPEND SOURCES ${CURRENT_SOURCES})
      #      message("SOURCES: ${SOURCES}")
    endif ()
    include_directories(generated)
  endif ()
endmacro()

include(../../../../cmake-tools/cmake-tools.cmake)

set(MYTHIC_EXTERNAL ${CMAKE_SOURCE_DIR}/external)
if (NOT ANDROID)
  set(MYTHIC_DEPENDENCIES ${PARENT_DIR}/dependencies/${GENERATOR_KEY})
else ()
  set(MYTHIC_DEPENDENCIES ${PARENT_DIR}/dependencies/mingw)
endif ()

if (MINGW)
  set(SDL_BIN ${MYTHIC_DEPENDENCIES}/sdl2/bin/SDL2.dll)
  set(SDL_LIB ${MYTHIC_DEPENDENCIES}/sdl2/lib/libSDL2.dll.a)
  #  set(OPENGL_LIB -lglu32 -lopengl32)
elseif (MSVC)
  set(SDL_BIN ${MYTHIC_DEPENDENCIES}/sdl2/lib/SDL2.dll)
  set(SDL_LIB ${MYTHIC_DEPENDENCIES}/sdl2/lib/SDL2.lib)
  #  set(OPENGL_LIB opengl32.lib)
endif ()


add_subdirectory(projects/misc/commoner)
add_subdirectory(projects/misc/logger)
add_subdirectory(projects/misc/quartz)
add_subdirectory(projects/misc/math)
add_subdirectory(projects/misc/vectoring)
add_subdirectory(projects/misc/textual)
add_subdirectory(projects/misc/spatial_old)
add_subdirectory(projects/misc/randomly)
add_subdirectory(projects/misc/promising)
add_subdirectory(projects/misc/threading)
add_subdirectory(projects/misc/containment)
add_subdirectory(projects/misc/mapping)
add_subdirectory(projects/misc/breeze)
add_subdirectory(projects/misc/songbird)
add_subdirectory(projects/misc/emission)
#add_subdirectory(external/boost_regex)

add_subdirectory(projects/generation/sculptor)
add_subdirectory(projects/generation/archaeology)
add_subdirectory(projects/client/general/resourceful)

include(projects/client/visual/visual.cmake)
add_subdirectory(projects/server/substance)
add_subdirectory(projects/client/visual/particular)
add_subdirectory(projects/client/input/haft)

add_subdirectory(projects/client/audio/audio_player)
add_subdirectory(projects/client/audio/aura_engineering)
add_subdirectory(projects/client/audio/aura_sequencing)
add_subdirectory(projects/client/audio/aura_processing)
add_subdirectory(projects/client/audio/aura_performing)
add_subdirectory(projects/client/audio/aura_performing_music)
add_subdirectory(projects/client/audio/aura_composing)
add_subdirectory(projects/client/audio/aura_producing)
add_subdirectory(projects/client/audio/aura_generation)
add_subdirectory(projects/client/audio/tuning)
add_subdirectory(projects/client/audio/foley)
add_subdirectory(projects/client/general/client)

add_subdirectory(projects/generation/architect)
add_subdirectory(projects/server/vineyard)
add_subdirectory(projects/server/sqling)
add_subdirectory(projects/server/ground)

add_subdirectory(projects/misc/platforming)
add_subdirectory(projects/misc/mythic)

add_subdirectory(projects/client/gui/bloom)
add_subdirectory(projects/client/gui/bloom_scenery)
add_subdirectory(projects/client/gui/bloom_lookinglass)

add_subdirectory(projects/client/gui/bloom_widgetry)
add_subdirectory(projects/client/gui/bloom_lab)
add_subdirectory(projects/lab/nobby)
add_subdirectory(projects/lab/bloom_nobby)
add_subdirectory(projects/lab/bloom_graphing)

add_subdirectory(projects/misc/achievements/achieving)
add_subdirectory(projects/misc/achievements/achieving_sqling)
add_subdirectory(projects/misc/achievements/achieving_bloom)

if (MINGW)
  #  add_subdirectory(projects/client/gui/bloom/test)
endif ()

if (MINGW OR MSCV)
  #  include(projects/lab/lab.cmake)
endif ()

if (ANDROID)
  add_subdirectory(platform/mythic_android)
  #  add_subdirectory(platform/workshop_android)

elseif (IOS)
  add_subdirectory(platform/mythic_ios)

else ()
  add_subdirectory(platform/desktop/desktop_display)
  add_subdirectory(platform/desktop/desktop_input)
  add_subdirectory(platform/desktop/mythic_desktop)

  #  add_subdirectory(platform/workshop)

endif ()

unset(LOCAL_HEADER)
set(LOCAL_FOOTER 1)
include(local-config.cmake OPTIONAL)

finish_cmake()

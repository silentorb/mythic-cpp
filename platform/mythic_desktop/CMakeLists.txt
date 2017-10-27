
create_library(mythic_desktop)

require(platforming desktop_display desktop_input shading shader_processing haft client logger audio_player resourceful shading)

include_directories(${MYTHIC_DEPENDENCIES}/sdl2/include)
link_external(sdl2 SDL2)

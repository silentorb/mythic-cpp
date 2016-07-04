
add_subdirectory(desktop_display)
add_subdirectory(desktop_input)

create_library(desktop)

require(mythic desktop_display desktop_input shading shader_processing haft client logger audio_player resourceful shading)

include_directories(
    ${MYTHIC_DEPENDENCIES}/sdl2/include
)

link_external(sdl2 SDL2)

#target_link_libraries(desktop
#  ${SDL_LIB}
#  )
#
#add_custom_command(TARGET desktop POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy ${SDL_BIN} $<TARGET_FILE_DIR:desktop>
#  )


create_library(desktop_display)

require(glow lookinglass shading logger frame)
link_external(sdl2 SDL2)

#include_directories(
#    ${MYTHIC_DEPENDENCIES}/sdl2/include
#)
#
#target_link_libraries(desktop_display
#  ${SDL_LIB}
#  )

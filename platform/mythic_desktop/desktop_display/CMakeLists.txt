
create_library(desktop_display)

require(glow lookinglass shading logger)

include_directories(
    ${MYTHIC_EXTERNAL}/SDL2-2.0.3/include
)

target_link_libraries(desktop_display
  ${SDL_LIB}
  )

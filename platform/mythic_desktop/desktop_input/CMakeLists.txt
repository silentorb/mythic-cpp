
create_library(desktop_input)

require(haft logger)

include_directories(
    ${MYTHIC_DEPENDENCIES}/sdl2/include
)

target_link_libraries(desktop_input
  ${SDL_LIB}
  )


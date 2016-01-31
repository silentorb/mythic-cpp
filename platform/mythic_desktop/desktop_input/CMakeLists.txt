
create_library(desktop_input)

require(haft logger)

include_directories(
    ${MYTHIC_EXTERNAL}/SDL2-2.0.3/include
)

target_link_libraries(desktop_input
  ${SDL_LIB}
  )


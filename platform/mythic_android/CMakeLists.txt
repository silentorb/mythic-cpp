create_library(mythic_android)

require(shading glow lookinglass mythic client haft audio_player resourceful)
add_system_libraries(EGL)
#target_link_libraries(mythic_android -lEGL)

find_package(math)
create_library(mythic_android)

require(shading glow lookinglass mythic client haft audio_player resourceful math)
add_system_libraries(EGL)
add_system_libraries(OpenSLES)

#target_link_libraries(mythic_android -lEGL)

#find_package(math)
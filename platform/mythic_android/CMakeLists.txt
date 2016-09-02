create_library(mythic_android)

require(shading shader_processing glow lookinglass mythic client haft audio_player resourceful math frame)
add_system_libraries(EGL)
add_system_libraries(OpenSLES)

#target_link_libraries(mythic_android -lEGL)

create_library(mythic_android)

require(shading shader_processing glow lookinglass mythic client haft
  platforming audio_player resourceful math frame)
add_system_libraries(EGL)
add_system_libraries(OpenSLES)

#target_link_libraries(mythic_android -lEGL)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/java DESTINATION ${CMAKE_BINARY_DIR}/src)
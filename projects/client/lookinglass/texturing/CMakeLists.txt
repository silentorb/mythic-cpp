
create_library(texturing)

require(glow resourceful shading)

add_resources(resources)

include_directories(
  ${MYTHIC_DEPENDENCIES}/libpng/include
)

if (MINGW)
  target_link_libraries(texturing
    ${MYTHIC_DEPENDENCIES}/libpng/lib/libpng.dll.a
    )

elseif (MSVC)

endif ()

add_custom_command(TARGET texturing POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${MYTHIC_DEPENDENCIES}/libpng/bin/libpng16.dll $<TARGET_FILE_DIR:shading>)
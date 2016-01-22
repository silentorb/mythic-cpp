
create_library(typography)

require(resourceful shading glow textual)

add_resources(resources)

if (MSVC)
  target_link_libraries(typography ${MYTHIC_EXTERNAL}/freetype/msvc/freetype262.lib)
  add_custom_command(TARGET typography POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${MYTHIC_EXTERNAL}/freetype/msvc/freetype262.dll $<TARGET_FILE_DIR:typography>
    )
elseif (MINGW)
  target_link_libraries(typography ${MYTHIC_EXTERNAL}/freetype/mingw64/libfreetype.dll.a)
  add_custom_command(TARGET typography POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${MYTHIC_EXTERNAL}/freetype/mingw64/libfreetype.dll $<TARGET_FILE_DIR:typography>
    )
endif ()

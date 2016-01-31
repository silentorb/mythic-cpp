
create_library(typography)

require(resourceful shading glow textual glass texturing)

if (MSVC)
  set(freetype_lib freetype.lib)
elseif (MINGW)
  set(freetype_lib libfreetype.dll.a)
endif ()

link_external(freetype)
#target_link_libraries(typography ${MYTHIC_DEPENDENCIES}/freetype/lib/${freetype_lib})
#add_custom_command(TARGET typography POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy ${MYTHIC_DEPENDENCIES}/freetype/bin/libfreetype.dll $<TARGET_FILE_DIR:typography>
#  )
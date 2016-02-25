
create_library(typography)

require(resourceful shading glow textual texturing)

#if (MSVC)
#  set(freetype_lib freetype.lib)
#elseif (MINGW)
#  set(freetype_lib libfreetype.dll.a)
#endif ()
link_external(zlib)
link_external_static(freetype)
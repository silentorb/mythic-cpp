
create_library(shading)

require(glow textual boost_regex logger resourceful)

add_resources(resources)

include_directories(
  ${MYTHIC_DEPENDENCIES}/libpng/include
)

if (MINGW)
  target_link_libraries(shading
    ${MYTHIC_DEPENDENCIES}/libpng/lib/libpng.dll.a
    )

elseif (MSVC)

endif ()
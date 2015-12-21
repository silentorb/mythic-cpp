
add_project(frame)

add_library(frame
  source/lookinglass/Desktop_Frame.cpp
  source/lookinglass/Desktop_Frame.h
  source/lookinglass/Frame.h
  )

include_directories(
  ${frame_includes}
  ${MYTHIC_EXTERNAL}/SDL2-2.0.3/include
)

target_link_libraries(frame
  ${MYTHIC_EXTERNAL}/SDL2-2.0.3/lib/libSDL2.dll.a
  )

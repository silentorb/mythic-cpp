add_project(frame)

#add_library(frame
#  source/lookinglass/Frame.h
#  )
set(frame_DIR ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)

include_directories(
  ${frame_includes}
)


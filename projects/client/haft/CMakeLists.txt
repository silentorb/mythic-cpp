
add_project(haft)

file(GLOB HEADERS "source/*.h")

create_library(haft
  source/haft/Action.h
  source/haft/Action.cpp
  source/haft/Input_Manager.h
  source/haft/Input_Manager.cpp
  source/haft/Device.h
  source/haft/Trigger.h
  source/haft/Trigger.cpp
  source/haft/Event.cpp
  source/haft/Event.h
  )

if (DEBUG_GLOW)
  add_definitions(-DDEBUG_GLOW=1)
endif ()

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/source
)

if (MSVC)
  include_directories(${CMAKE_CURRENT_LIST_DIR}/glad/include)
#  include_directories(${CMAKE_CURRENT_LIST_DIR}/glloader)

elseif (MINGW)
  include_directories(${CMAKE_CURRENT_LIST_DIR}/glloader)

elseif (ANDROID)
  include_directories(${CMAKE_CURRENT_LIST_DIR}/android)

endif ()
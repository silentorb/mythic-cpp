create_library(promising)
require(commoner)
add_definitions(-DPROMISING_LIB)

option(DEBUG_PROMISES "Debug Promises" OFF)
if (DEBUG_PROMISES)
  require(debugging)
  add_definitions(-DDEBUG_PROMISES)
endif ()
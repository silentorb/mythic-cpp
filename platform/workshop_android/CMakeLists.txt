set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(workshop)

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/source
)

require(mythic_android mythic lab)

set(application_namespace com.silentorb PARENT_SCOPE)
set(application_entry_lib workshop)
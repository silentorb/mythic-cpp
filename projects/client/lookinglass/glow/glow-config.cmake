
include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/source
)

if (MSVC)
  include_directories(${CMAKE_CURRENT_LIST_DIR}/glad/include)
endif()
#message("a")
find_package(math)
#message("b ${${CURRENT_TARGET}_includes}")

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/source
)
#message("d ${${CURRENT_TARGET}_includes}")
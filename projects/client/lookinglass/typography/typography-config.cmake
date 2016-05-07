find_package(math)

include_external_directory(freetype freetype2)
include_directories(
#  ${MYTHIC_DEPENDENCIES}/freetype/include/freetype2
  ${CMAKE_CURRENT_LIST_DIR}/source
)
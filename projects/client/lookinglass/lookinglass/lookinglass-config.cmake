#
set(lookinglass_includes
  ${CMAKE_CURRENT_LIST_DIR}/source
#  ${CMAKE_SOURCE_DIR}/external/freetype-2.6/include
)
##message("testing ${CMAKE_SOURCE_DIR}/external/freetype-2.6/include")
#string(REPLACE "\\" "/" "BIN_PATH" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
##set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(lookinglass_libs
  $<TARGET_FILE:lookinglass>
#  ${CMAKE_SOURCE_DIR}/external/freetype-2.6/bin/release-64x/freetype26.lib
)
#print_info()
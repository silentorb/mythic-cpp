add(glaze_test_utility)

create_test(glaze_test)
require(glaze glaze_test_utility textual)
add_definitions(-DSHADERS_PATH=${CMAKE_CURRENT_LIST_DIR}/shaders)


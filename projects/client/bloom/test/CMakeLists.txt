
create_executable(bloom_test)
require(bloom promising)
link_external_static(googletest gtest)
if (MINGW)
  target_link_libraries(bloom_test "${MYTHIC_DEPENDENCIES}/googletest/lib/libgtest_main.a")
elseif (MSVC)

endif ()

#include <bloom/flowers/Box.h>
#include "gtest/gtest.h"

using namespace bloom;
using namespace glm;

TEST(Layout_Test, simple_pixel_measurements) {
  flowers::Box box(nullptr);

  vec2 root_position(0, 10);
  Parent_Dimensions root_bounds = {
    {800, false},
    {600, false},
  };

  {
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(0, bounds.x.near);
  }

  {
    box.update_relative(root_bounds);
    box.update_absolute(root_position);
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(400, bounds.x.near);
  }

  box.set_left(10);
  box.set_top(10);
  box.set_width(100);

  {
    box.update_relative(root_bounds);
    box.update_absolute(root_position);
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(10, bounds.x.near);
    EXPECT_EQ(20, bounds.y.near);
    EXPECT_EQ(110, bounds.x.far);
  }

}

TEST(Layout_Test, percentage_measurements) {
  flowers::Box box(nullptr);

  vec2 root_position(0, 10);
  Parent_Dimensions root_bounds = {
    {200, false},
    {200, false},
  };

  box.set_right({Measurements::percent, 10});
  box.set_width({Measurements::percent, 60});

  box.set_top({Measurements::percent, 20});
  box.set_bottom({Measurements::percent, 30});

  box.update_relative(root_bounds);
  box.update_absolute(root_position);
  auto &bounds = box.get_absolute_bounds();
  EXPECT_EQ(60, bounds.x.near);
  EXPECT_EQ(20, bounds.x.far);
  EXPECT_EQ(50, bounds.y.near);
  EXPECT_EQ(70, bounds.y.far);
}

TEST(Layout_Test, percentage_perpendicular_measurements) {
  flowers::Box box(nullptr);

  vec2 root_position(0, 0);
  Parent_Dimensions root_bounds = {
    {200, false},
    {100, false},
  };

  box.set_height({Measurements::percent_perpendicular, 25});

  box.update_relative(root_bounds);
  box.update_absolute(root_position);
  auto &bounds = box.get_absolute_bounds();
  EXPECT_EQ(25, bounds.y.near);
  EXPECT_EQ(75, bounds.y.far);
}

TEST(Layout_Test, children) {
  flowers::Box box(nullptr);
  auto &child = *new flowers::Box(&box);

  vec2 root_position(10, 0);
  Parent_Dimensions root_bounds = {
    {200, false},
    {200, false},
  };

  box.set_left(10);
  child.set_left(10);
  child.set_width(20);

  box.update_relative(root_bounds);
  box.update_absolute(root_position);

  auto &child_bounds = child.get_absolute_bounds();
  EXPECT_EQ(30, child_bounds.x.near);

  auto &box_bounds = box.get_absolute_bounds();
  EXPECT_EQ(20, box_bounds.x.near);
  EXPECT_EQ(50, box_bounds.x.far);
}


TEST(Layout_Test, all_stretch) {
  flowers::Box box(nullptr);
  auto &child = *new flowers::Box(&box);

  vec2 root_position(0, 0);
  Parent_Dimensions root_bounds = {
    {200, false},
    {200, false},
  };

  child.set_width(80);

  box.update_relative(root_bounds);
  box.update_absolute(root_position);

  auto &child_bounds = child.get_absolute_bounds();
  EXPECT_EQ(60, child_bounds.x.near);
  EXPECT_EQ(140, child_bounds.x.far);

  auto &box_bounds = box.get_absolute_bounds();
  EXPECT_EQ(60, box_bounds.x.near);
  EXPECT_EQ(140, box_bounds.x.far);
}

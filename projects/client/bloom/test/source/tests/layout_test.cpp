#include <bloom/flowers/Box.h>
#include "gtest/gtest.h"

using namespace bloom;
using namespace glm;

TEST(Layout_Test, simple_pixel_measurements) {
  flowers::Box box(nullptr);

  Parent_Dimensions root_bounds = {
    {0,  800, false},
    {10, 600, false},
  };

  {
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(0, bounds.x.near);
  }

  {
    box.update_layout(root_bounds);
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(400, bounds.x.near);
  }

  box.set_left(10);
  box.set_top(10);
  box.set_width(100);

  {
    box.update_layout(root_bounds);
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(10, bounds.x.near);
    EXPECT_EQ(20, bounds.y.near);
    EXPECT_EQ(110, bounds.x.far);
  }

}

TEST(Layout_Test, percentage_measurements) {
  flowers::Box box(nullptr);

  Parent_Dimensions root_bounds = {
    {0,  200, false},
    {10, 200, false},
  };

  box.set_right({Measurements::percent, 10});
  box.set_width({Measurements::percent, 60});

  box.set_top({Measurements::percent, 20});
  box.set_bottom({Measurements::percent, 30});

  box.update_layout(root_bounds);
  auto &bounds = box.get_absolute_bounds();
  EXPECT_EQ(60, bounds.x.near);
  EXPECT_EQ(20, bounds.x.far);
  EXPECT_EQ(50, bounds.y.near);
  EXPECT_EQ(70, bounds.y.far);
}

TEST(Layout_Test, percentage_perpendicular_measurements) {
  flowers::Box box(nullptr);

  Parent_Dimensions root_bounds = {
    {0, 200, false},
    {0, 100, false},
  };

  box.set_height({Measurements::percent_perpendicular, 25});

  box.update_layout(root_bounds);
  auto &bounds = box.get_absolute_bounds();
  EXPECT_EQ(25, bounds.y.near);
  EXPECT_EQ(25, bounds.y.far);
}

TEST(Layout_Test, children) {
  flowers::Box box(nullptr);
  auto &child = *new flowers::Box(&box);

  Parent_Dimensions root_bounds = {
    {10, 200, false},
    {0,  200, false},
  };

  box.set_left(10);
  child.set_left(10);
  child.set_width(20);

  box.update_layout(root_bounds);

  auto &child_bounds = child.get_absolute_bounds();
  EXPECT_EQ(30, child_bounds.x.near);

  auto &box_bounds = box.get_absolute_bounds();
  EXPECT_EQ(20, box_bounds.x.near);
  EXPECT_EQ(50, box_bounds.x.far);
}

//TEST(Layout_Test, fit_contents) {
//  flowers::Box box(nullptr);
//  auto &child = *new flowers::Box(&box);
//
//  Parent_Dimensions root_bounds = {
//    {10, 200, false},
//    {0,  200, false},
//  };
//
//  box.set_left(10);
//  child.set_left(10);
//
//  box.update_layout(root_bounds);
//  auto &bounds = child.get_absolute_bounds();
//  EXPECT_EQ(30, bounds.x.near);
//
//}
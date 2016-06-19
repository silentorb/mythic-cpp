#include <bloom/flowers/Box.h>
#include <bloom/flowers/List.h>
#include "gtest/gtest.h"

using namespace bloom;
using namespace glm;

TEST(Layout_Test, simple_pixel_measurements) {
  flowers::Box box(nullptr);

  vec2 root_position(0, 10);
  vec2 root_bounds = {
    800,
    600
  };

  {
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(0, bounds.x.near);
  }

  {
    box.update_dimensions(root_bounds);
    box.update_position(root_position, root_bounds);
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(0, bounds.x.near);
    EXPECT_EQ(800, bounds.x.far);
  }

  box.set_left(10);
  box.set_top(10);
  box.set_width(100);

  {
    box.update_dimensions(root_bounds);
    box.update_position(root_position, root_bounds);
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(10, bounds.x.near);
    EXPECT_EQ(20, bounds.y.near);
    EXPECT_EQ(110, bounds.x.far);
  }

}

TEST(Layout_Test, percentage_measurements) {
  flowers::Box box(nullptr);

  vec2 root_position(0, 10);
  vec2 root_bounds = {
    200,
    200
  };

  box.set_right({Measurements::percent, 10});
  box.set_width({Measurements::percent, 60});

  box.set_top({Measurements::percent, 20});
  box.set_bottom({Measurements::percent, 30});

  box.update_dimensions(root_bounds);
  box.update_position(root_position, root_bounds);
  auto &bounds = box.get_absolute_bounds();
  EXPECT_EQ(60, bounds.x.near);
  EXPECT_EQ(20, bounds.x.far);
  EXPECT_EQ(50, bounds.y.near);
  EXPECT_EQ(70, bounds.y.far);
}

TEST(Layout_Test, percentage_perpendicular_measurements) {
  flowers::Box box(nullptr);

  vec2 root_position(0, 0);
  vec2 root_bounds = {
    200,
    100
  };

  box.set_height({Measurements::percent_perpendicular, 25});

  box.update_dimensions(root_bounds);
  box.update_position(root_position, root_bounds);
  auto &bounds = box.get_absolute_bounds();
  EXPECT_EQ(25, bounds.y.near);
  EXPECT_EQ(75, bounds.y.far);
}

TEST(Layout_Test, children) {
  flowers::Box box(nullptr);
  auto &child = *new flowers::Box(&box);

  vec2 root_position(10, 0);
  vec2 root_bounds = {
    200,
    200,
  };

  box.set_left(10);
  child.set_left(10);
  child.set_width(20);

  box.update_dimensions(root_bounds);
  box.update_position(root_position, root_bounds);

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
  vec2 root_bounds = {
    200,
    200
  };

  child.set_width(80);

  box.update_dimensions(root_bounds);
  box.update_position(root_position, root_bounds);

  auto &child_bounds = child.get_absolute_bounds();
  EXPECT_EQ(60, child_bounds.x.near);
  EXPECT_EQ(140, child_bounds.x.far);

  auto &box_bounds = box.get_absolute_bounds();
  EXPECT_EQ(60, box_bounds.x.near);
  EXPECT_EQ(140, box_bounds.x.far);
}

TEST(Layout_Test, list) {
  flowers::Box box(nullptr);
  auto &list = *new flowers::List(&box, flowers::Arrangement::down, 10);
  auto &first = *new flowers::Box(&list);
  auto &second = *new flowers::Box(&list);

  vec2 root_position(0, 0);
  vec2 root_bounds = {
    100,
    100
  };

  first.set_width(20);
  first.set_height(10);
  second.set_width(20);
  second.set_height(10);

  box.update_dimensions(root_bounds);
  box.update_position(root_position, root_bounds);

  {
    auto &bounds = first.get_absolute_bounds();
    EXPECT_EQ(40, bounds.x.near);
    EXPECT_EQ(60, bounds.x.far);
    EXPECT_EQ(35, bounds.y.near);
    EXPECT_EQ(45, bounds.y.far);
  }

  {
    auto &bounds = second.get_absolute_bounds();
    EXPECT_EQ(40, bounds.x.near);
    EXPECT_EQ(60, bounds.x.far);
    EXPECT_EQ(55, bounds.y.near);
    EXPECT_EQ(65, bounds.y.far);
  }
}

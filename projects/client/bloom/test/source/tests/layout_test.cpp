#include <bloom/flowers/Box_Group.h>
#include <bloom/flowers/List.h>
#include "gtest/gtest.h"

using namespace bloom;
using namespace glm;

TEST(Layout_Test, simple_pixel_measurements) {
  flowers::Box_Group box(nullptr);

  vec2 root_position(0, 10);
  vec2 root_bounds = {
    800,
    600
  };

  {
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(0, bounds.position.x);
  }

  {
    box.update_dimensions(root_bounds);
    box.update_position(root_position, root_bounds);
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(0, bounds.position.x);
    EXPECT_EQ(800, bounds.position.x + bounds.dimensions.x);
  }

  box.set_left(10);
  box.set_top(10);
  box.set_width(100);

  {
    box.update_dimensions(root_bounds);
    box.update_position(root_position, root_bounds);
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(10, bounds.position.x);
    EXPECT_EQ(20, bounds.position.y);
    EXPECT_EQ(110, bounds.position.x + bounds.dimensions.x);
  }

}

TEST(Layout_Test, percentage_measurements) {
  flowers::Box_Group box(nullptr);

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
  EXPECT_EQ(60, bounds.position.x);
  EXPECT_EQ(120, bounds.dimensions.x);
  EXPECT_EQ(50, bounds.position.y);
  EXPECT_EQ(100, bounds.dimensions.y);
}

TEST(Layout_Test, percentage_perpendicular_measurements) {
  flowers::Box_Group box(nullptr);

  vec2 root_position(0, 0);
  vec2 root_bounds = {
    200,
    100
  };

  box.set_height({Measurements::percent_perpendicular, 25});

  box.update_dimensions(root_bounds);
  box.update_position(root_position, root_bounds);
  auto &bounds = box.get_absolute_bounds();
  EXPECT_EQ(25, bounds.position.y);
  EXPECT_EQ(75, bounds.position.y + bounds.dimensions.y);
}

TEST(Layout_Test, children) {
  flowers::Box_Group box(nullptr);
  auto &child = *new flowers::Box_Group(&box);

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
  EXPECT_EQ(30, child_bounds.position.x);

  auto &box_bounds = box.get_absolute_bounds();
  EXPECT_EQ(20, box_bounds.position.x);
  EXPECT_EQ(20, box_bounds.dimensions.x);
}

TEST(Layout_Test, all_stretch) {
  flowers::Box_Group box(nullptr);
  auto &child = *new flowers::Box_Group(&box);

  vec2 root_position(0, 0);
  vec2 root_bounds = {
    200,
    200
  };

  child.set_width(80);

  box.update_dimensions(root_bounds);
  box.update_position(root_position, root_bounds);

  auto &child_bounds = child.get_absolute_bounds();
  EXPECT_EQ(60, child_bounds.position.x);
  EXPECT_EQ(80, child_bounds.dimensions.x);

  auto &box_bounds = box.get_absolute_bounds();
  EXPECT_EQ(60, box_bounds.position.x);
  EXPECT_EQ(80, box_bounds.dimensions.x);
}

TEST(Layout_Test, list) {
  flowers::Box_Group box(nullptr);
  auto &list = *new flowers::List(flowers::Arrangement::down, 10, &box);
  auto &first = *new flowers::Box_Group(&list);
  auto &second = *new flowers::Box_Group(&list);

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
    auto &bounds = box.get_absolute_bounds();
    EXPECT_EQ(40, bounds.position.x);
    EXPECT_EQ(20, bounds.dimensions.x);
    EXPECT_EQ(35, bounds.position.y);
    EXPECT_EQ(30, bounds.dimensions.y);
  }

  {
    auto &bounds = first.get_absolute_bounds();
    EXPECT_EQ(40, bounds.position.x);
    EXPECT_EQ(20, bounds.dimensions.x);
    EXPECT_EQ(35, bounds.position.y);
    EXPECT_EQ(10, bounds.dimensions.y);
  }

  {
    auto &bounds = second.get_absolute_bounds();
    EXPECT_EQ(40, bounds.position.x);
    EXPECT_EQ(20, bounds.dimensions.x);
    EXPECT_EQ(55, bounds.position.y);
    EXPECT_EQ(10, bounds.dimensions.y);
  }
}


TEST(Layout_Test, padding) {
  flowers::Box_Group box(nullptr);
  auto &padding = *new flowers::Box_Group(&box);
  auto &text = *new flowers::Box_Group(&padding);

  vec2 root_position(0, 0);
  vec2 root_bounds = {
    200,
    200
  };

  padding.set_top(10);
  padding.set_bottom(10);

  text.set_height(20);
  box.set_top(10);

  box.update_dimensions(root_bounds);
  box.update_position(root_position, root_bounds);

  auto &child_bounds = text.get_absolute_bounds();

  auto &box_bounds = box.get_absolute_bounds();
  EXPECT_EQ(40, box_bounds.dimensions.y);
  EXPECT_EQ(10, box_bounds.position.y);
}


//TEST(Layout_Test, child_to_parent_to_child_resolution) {
//  flowers::Box box(nullptr);
//  auto &scaling = *new flowers::Box(&box);
//  auto &fixed = *new flowers::Box(&scaling);
//
//  vec2 root_position(0, 0);
//  vec2 root_bounds = {200, 200};
//
//  scaling.set_height({Measurements:: percent,100});
//
//  fixed.set_height(55);
//  box.set_top(0);
//
//  box.update_dimensions(root_bounds);
//  box.update_position(root_position, root_bounds);
//
//  {
//    auto &bounds = box.get_absolute_bounds();
//    EXPECT_EQ(55, bounds.dimensions.y);
//  }
//
//  {
//    auto &bounds = scaling.get_absolute_bounds();
//    EXPECT_EQ(55, bounds.dimensions.y);
//  }
//}
//

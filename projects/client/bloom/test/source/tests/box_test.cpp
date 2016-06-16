#include <bloom/Garden.h>
#include <bloom/flowers/Scrollable.h>
#include "gtest/gtest.h"
#include "glm/glm.hpp"
#include "mocks/Mock_Draw_Interface.h"

#define NEAR_RANGE 0.00001

Flower_Old *create_row(Flower_Old *parent) {
  auto row = new Flower_Old(parent);
  row->set_height(Measurement(20));
  return row;
}

TEST(Box_Test, test_test) {
  Mock_Draw_Interface draw;
  Garden garden(draw);
  auto list = new Flower_Old(&garden.get_root());
  list->set_arrangement(Arrangement::down);
  list->set_spacing(Measurement(10));
  auto first = create_row(list);
  auto second = create_row(list);
  auto third = create_row(list);

  garden.update_layout();

  EXPECT_EQ(0, first->get_cache().y.near);
  EXPECT_EQ(30, second->get_cache().y.near);
  EXPECT_EQ(60, third->get_cache().y.near);
}

Scrollable *create_scrollable_list(Garden &garden) {
  auto list = new Scrollable(&garden.get_root());
  list->set_arrangement(Arrangement::down);
  list->set_spacing(Measurement(0));
  list->set_height(30);
  list->set_top(0);
  auto first = create_row(list);
  auto second = create_row(list);
  auto third = create_row(list);
  return list;
}

TEST(Box_Test, scrolling1) {
  Mock_Draw_Interface draw;
  Garden garden(draw);
  auto list = create_scrollable_list(garden);

  garden.update_layout();

  EXPECT_EQ(30, list->get_cache().y.length);
  EXPECT_EQ(90, list->get_content_height());
}

TEST(Box_Test, scrolling2) {
  Mock_Draw_Interface draw;
  Garden garden(draw);
  auto list = create_scrollable_list(garden);

  list->set_offset({0, -20});
  garden.update_layout();

  EXPECT_EQ(30, list->get_cache().y.length);
  EXPECT_EQ(90, list->get_content_height());
}

TEST(Box_Test, list_align_bottom) {
  Mock_Draw_Interface draw;
  Garden garden(draw);
  auto list = new Flower_Old(&garden.get_root());
  list->set_arrangement(Arrangement::down);
  list->set_bottom(10);
  auto first = create_row(list);
  auto second = create_row(list);

  garden.update_layout();

  EXPECT_EQ(1000 - 40 - 10, list->get_cache().y.near);
  EXPECT_EQ(1000 - 40 - 10, first->get_cache().y.near);
  EXPECT_EQ(1000 - 20 - 10, second->get_cache().y.near);
}
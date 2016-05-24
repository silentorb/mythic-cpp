#include <bloom/Garden.h>
#include "gtest/gtest.h"
#include "glm/glm.hpp"
#include "mocks/Mock_Draw_Interface.h"

#define NEAR_RANGE 0.00001

Flower *create_row(Flower *parent) {
  auto row = new Flower(parent);
  row->set_height(Simple_Measurement(20));
  return row;
}

TEST(Box_Test, test_test) {
  Mock_Draw_Interface draw;
  Garden garden(draw);
  auto list = new Flower(&garden.get_root());
  list->set_arrangement(Arrangement::down);
  list->set_spacing(Simple_Measurement(10));
  auto first = create_row(list);
  auto second = create_row(list);
  auto third = create_row(list);

  garden.update_layout();

  EXPECT_EQ(0, first->get_cache().y.near);
  EXPECT_EQ(30, second->get_cache().y.near);
  EXPECT_EQ(60, third->get_cache().y.near);
}
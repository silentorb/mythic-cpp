#include "gtest/gtest.h"
#include <glaze/definition/Material.h>
#include <glaze/brushes/GL_Desktop_Brush.h>
#include "glaze_test/utility.h"

using namespace std;

using namespace glaze::definition;
using namespace glaze;

TEST(Box_Test, test_test) {

  auto code = load_shader("colored.vertex");

  Material material;
  material.add_inputs(
    {
      {types::vec3, "position"},
      {types::vec3, "normal"},
      {types::vec4, "color"},
    });

  material.add_uniforms(
    {
      {types::mat4, "model"},
      {types::mat4, "normal_transform"},
      {types::vec4, "color_filter"},
    });

  auto donut = brushes::GL_Desktop_Brush(material);
  compare_text(code, donut.vertex);
//  EXPECT_EQ(0, 1);
//  EXPECT_EQ(30, second->get_cache().y.near);
//  EXPECT_EQ(60, third->get_cache().y.near);
}
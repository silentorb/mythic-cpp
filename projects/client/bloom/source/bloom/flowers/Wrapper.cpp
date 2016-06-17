#include "Wrapper.h"
#include "bloom/layout/Axis.h"

namespace bloom {
  namespace flowers {


    void Wrapper::render() {
      Flower_Old::render();
      flower->render();
    }

    void Wrapper::update_absolute_dimensions(const Axis_Values_Old &parent_values, const vec2 margin) {
      auto pixel_dimensions = converter.convert_to_pixels({parent_values.x.length, parent_values.y.length});
      Parent_Dimensions parent_dimensions{
        {pixel_dimensions.x, false},
        {pixel_dimensions.y, false},
      };
      flower->update_relative(parent_dimensions);
      auto parent_position = converter.convert_to_pixels({parent_values.x.near, parent_values.y.near});
      flower->update_absolute(parent_position);

      auto &flower_bounds = flower->get_absolute_bounds();
      auto original_parent_dimensions = vec2(parent_values.x.length, parent_values.y.length);

      auto &converter = get_converter();
//      dimensions.set_x(get_converter().convert_to_units(flower_bounds.x.far - flower_bounds.x.near));
//      dimensions.set_y(get_converter().convert_to_units(flower_bounds.y.far - flower_bounds.y.near));
      
      axis_cache.x.near = converter.convert_to_units(flower_bounds.x.near);
      axis_cache.x.absolute_far = converter.convert_to_units(flower_bounds.x.far);
      axis_cache.x.length = axis_cache.x.absolute_far - axis_cache.x.near;

      axis_cache.y.near = converter.convert_to_units(flower_bounds.y.near);
      axis_cache.y.absolute_far = converter.convert_to_units(flower_bounds.y.far);
      axis_cache.y.length = axis_cache.y.absolute_far - axis_cache.y.near;

    }
  }
}
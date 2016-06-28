#include "Wrapper.h"
#include "bloom/layout/Axis.h"

namespace bloom {
  namespace flowers {
		int _k = 0;

		Wrapper::Wrapper(Flower_Old *parent, Flower *flower) : Flower_Old(parent), flower(flower) { 
			++_k; 
		}
		Wrapper::~Wrapper() {
			--_k;
		}

    void Wrapper::render() {
      Flower_Old::render();
      flower->render();
    }

    void Wrapper::update_absolute_dimensions(const Axis_Values_Old &parent_values, const vec2 margin) {
      auto pixel_dimensions = converter.convert_to_pixels({parent_values.x.length, parent_values.y.length});
      glm::vec2 parent_dimensions{pixel_dimensions.x, pixel_dimensions.y};
      flower->update_dimensions(parent_dimensions);
      auto parent_position = converter.convert_to_pixels({parent_values.x.near, parent_values.y.near});
      flower->update_position(parent_position, parent_dimensions);

      auto &flower_bounds = flower->get_absolute_bounds();
      auto original_parent_dimensions = vec2(parent_values.x.length, parent_values.y.length);

      auto &converter = get_converter();
//      dimensions.set_x(get_converter().convert_to_units(flower_bounds.x.far - flower_bounds.x.near));
//      dimensions.set_y(get_converter().convert_to_units(flower_bounds.y.far - flower_bounds.y.near));

      axis_cache.x.near = converter.convert_to_units(flower_bounds.position.x);
      axis_cache.x.length = converter.convert_to_units(flower_bounds.dimensions.x);
      axis_cache.x.absolute_far = axis_cache.x.near + axis_cache.x.length;

      axis_cache.y.near = converter.convert_to_units(flower_bounds.position.y);
      axis_cache.y.length = converter.convert_to_units(flower_bounds.dimensions.y);
      axis_cache.y.absolute_far = axis_cache.y.near + axis_cache.y.length;

    }

    bool Wrapper::check_event_new(const songbird::Song<Flower_Delegate> &event_type, const vec2 &point) {
      return flower->check_event(event_type, point);
    }

  }
}
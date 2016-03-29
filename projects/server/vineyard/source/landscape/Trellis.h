#pragma once

#include "dllexport.h"
#include "Property.h"
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

namespace landscape {

  class MYTHIC_EXPORT Trellis {
      const string name;
      vector<Property> properties;
      int block_size;

  public:
      Trellis(const string &name, initializer_list<Property> initializer);


      const string &get_name() const {
        return name;
      }

      const vector<Property> &get_properties() const {
        return properties;
      }

      const Property &get_property(const string &property_name) const {
        for (auto &property: properties) {
          if (property.get_name() == property_name)
            return property;
        }

        throw runtime_error("Could not find property " + property_name);
      }

      const Property &get_property(int index) const {
        return properties[index];
      }

      int get_block_size()const {
        return block_size;
      }
  };
}
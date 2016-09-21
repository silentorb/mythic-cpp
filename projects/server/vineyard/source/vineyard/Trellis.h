#pragma once

#include "Property.h"
#include "identity.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <functional>

using namespace std;
using namespace vineyard;

namespace vineyard {

  using Seedery = std::function<void *(int)>;
  using Trellis_Map = std::function<Trellis &(const std::string&)>;

  class Trellis {
      const string name;
      vector<Property> properties;
      int offset;
      Seedery seedery;
      Identity _next_id = 1;

  public:
      Trellis(const string &name, initializer_list<Property> initializer, int offset,Seedery seedery = nullptr);

      const string &get_name() const {
        return name;
      }

      const vector<Property> &get_properties() const {
        return properties;
      }

//       vector<Property> &get_properties()  {
//        return properties;
//      }

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

      int get_block_size() const {
        return offset;
      }

      void finalize(const Trellis_Map &library);

      void *find_seed(int id) const {
        return seedery(id);
      }

      void reset_next_id() {
        _next_id = 1;
      }

      void set_next_id(Identity value) {
        _next_id = value;
      }

      Identity next_id() {
        return _next_id++;
      }
  };
}
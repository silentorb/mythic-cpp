#pragma once

#include "aura_export.h"
#include <vector>
#include <aura/music/performance/Stroke.h>
#include "Property.h"

using namespace std;

namespace aura {
  namespace graphing {

    class Node {
        friend class Property;

        vector<Property *> properties;
        void add_property(Property &property);
        size_t data_size;

    public:
        virtual ~Node() {}

        Property &get_first_output() const;

        vector<Property *> &get_properties() {
          return properties;
        }

        const vector<Property *> &get_properties() const {
          return properties;
        }

        virtual void update(const Stroke &stroke, void *data) = 0;

        int get_data_size() const {
          return data_size;
        };

        template<typename T>
        void connect(Output<T> &output, Input<T> &input) {
          input.set_other_property(&output);
        }
    };
  }
}
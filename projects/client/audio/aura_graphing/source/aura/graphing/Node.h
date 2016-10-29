#pragma once

#include "aura_export.h"
#include <vector>
#include <aura/Stroke.h>
#include "Property.h"
#include <memory>
#include <commoner/debug-macro.h>

using namespace std;

namespace aura {
  namespace graphing {

    typedef function<void(const Stroke &, void *)> Node_Update;

    struct Node_Instance : no_copy {
        vector<unique_ptr<Property>> properties;
        Node_Update update;
        size_t data_size = 0;

#ifdef COMMONER_DEBUG
        string name;
        Node_Instance(const string &name, const Node_Update &update) :
          name(name), update(update) {}

        ~Node_Instance()
        {
          int k = 0;
        }
#else

        Node_Instance(const Node_Update &update) :
          update(update) {}

#endif

        Property &get_first_output() const;
        Input_Base &get_first_input() const;

        vector<unique_ptr<Property>> &get_properties() {
          return properties;
        }

        const vector<unique_ptr<Property>> &get_properties() const {
          return properties;
        }

        const Node_Update &get_update() const {
          return update;
        }

        int get_data_size() const {
          return data_size;
        };

        void finalize();

    };

    class AURA_EXPORT Node {
        friend class Property;

        std::shared_ptr<Node_Instance> instance;
        void add_property(Property *property);

    private:
        Node(void*);

    public:
#ifdef COMMONER_DEBUG
        Node(const string &name, const initializer_list<Property *> property_initializer, const Node_Update &update);
#else
        Node(const initializer_list<Property *> property_initializer, const Node_Update &update);
#endif
        Node(const Node &node);

        Node(const shared_ptr<Node_Instance> &new_instance) : instance(new_instance) {}

        Node(float value);

        const shared_ptr<Node_Instance> &get_instance() const {
          return instance;
        }

        vector<unique_ptr<Property>> &get_properties() {
          return instance->properties;
        }

        const vector<unique_ptr<Property>> &get_properties() const {
          return instance->properties;
        }

        Node_Update &get_update() const {
          return instance->update;
        }

        int get_data_size() const {
          return instance->data_size;
        };

        bool is_empty() const{
          return instance->get_properties().size() == 0;
        }

        static Node create_empty();

        Node operator >>(const Node &other);
    };

#ifdef COMMONER_DEBUG
#define NODE_ID(name) name,
#else
#define NODE_ID(name)
#endif
  }
}
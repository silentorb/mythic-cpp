#pragma once

#include "aura_export.h"
#include "Connection.h"
#include <vector>
#include <aura/music/performance/Stroke.h>
#include <functional>

using namespace std;

namespace aura {
  namespace graphing {

    class Property;

    class Node {
        friend class Property;

        vector<Property *> properties;
        void add_property(Property &property);

    protected:
        Property &get_first_output() const;

    public:
        virtual  ~Node() {}

        vector<Property *> &get_properties() {
          return properties;
        }

        virtual int get_data_size() const = 0;
    };

    class AURA_EXPORT Property {
    public:
        Property(Node *parent) {
          parent->add_property(*this);
        }

        enum class Direction {
            output,
            input,
        };

        virtual Direction get_direction() const = 0;
        virtual Node *get_other_node() const = 0;
    };

    template<typename T>
    class AURA_EXPORT Input : public Property {
        Node *other_node = nullptr;

    public:
        Input(Node *parent) : Property(parent) {}

        virtual Direction get_direction() const override {
          return Direction::input;
        }

        virtual Node *get_other_node() const override {
          return other_node;
        }

        void set_node(Node *value) {
          other_node = value;
        }
    };

    template<typename T>
    class AURA_EXPORT Output : public Property {
    public:
        Output(Node *parent) : Property(parent) {}

        virtual Direction get_direction() const override {
          return Direction::output;
        }

        virtual Node *get_other_node() const override {
          return nullptr;
        }
    };

    template<typename Data>
    class AURA_EXPORT Data_Node : public Node {

    public:
        virtual ~Data_Node() {}

        template<typename T>
        operator Output<T> &() const {
          return (Output<T> &) get_first_output();
        }

        virtual void update(const Stroke &stroke, Data &data) = 0;

        virtual int get_data_size() const override {
          return sizeof(Data);
        }
    };
  }
}
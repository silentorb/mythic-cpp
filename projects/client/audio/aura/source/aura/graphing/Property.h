#pragma once

#include "aura_export.h"

namespace aura {
  namespace graphing {

    class Node;

    class AURA_EXPORT Property {
        friend class Node;

        size_t offset;
        Node &node;

    public:
        Property(Node *parent);

        enum class Direction {
            output,
            input,
        };

        virtual Direction get_direction() const = 0;
        virtual Node *get_other_node() const = 0;
        virtual Property *get_other_property() const = 0;
        virtual size_t get_size() const = 0;
        virtual void assign(void *data, void *other_data, Property &other_property) = 0;

        size_t get_offset() const {
          return offset;
        }

        Node &get_node() const {
          return node;
        }
    };

    template<typename T>
    class AURA_EXPORT Input : public Property {
        Property *other_property = nullptr;

    public:
        Input(Node *parent) : Property(parent) {}

        virtual Direction get_direction() const override {
          return Direction::input;
        }

        virtual Node *get_other_node() const override {
          return other_property
                 ? &other_property->get_node()
                 : nullptr;
        }

        void set_other_property(Property * property){
          other_property = property;
        }

        virtual size_t get_size() const override {
          return sizeof(T);
        }

        virtual void assign(void *data, void *other_data, Property &other_property) override {
          *(T *) (data + get_offset()) = *(T *) (other_data + other_property.get_offset());
        }

        virtual Property *get_other_property() const override {
          return other_property;
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

        virtual size_t get_size() const override {
          return sizeof(T);
        }

        virtual void assign(void *data, void *other_data, Property &other_property) override;

        virtual Property *get_other_property() const override {
          return nullptr;
        }
    };

  }
}
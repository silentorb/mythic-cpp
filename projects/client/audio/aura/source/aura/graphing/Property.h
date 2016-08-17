#pragma once

#include "aura_export.h"
#include <cstdlib>
#include <stdexcept>
#include <functional>

namespace aura {
  class Producer;

  namespace graphing {

    class Node;


    class AURA_EXPORT Property {
        friend class Node;

        size_t offset;

    protected:
        void initialize_node(Node &node);

    public:
        enum class Type {
            output,
            input,
            constant,
            internal
        };

        virtual Type get_type() const = 0;
        virtual size_t get_size() const = 0;

        size_t get_offset() const {
          return offset;
        }

    };

    class Node_Property : public Property {
        Node &node;

    public:
        Node_Property(Node &node) : node(node) {
          initialize_node(node);
        }

        Node &get_node() const {
          return node;
        }
    };

    class Output_Base : public Node_Property {
    public:
        Output_Base(Node &node) : Node_Property(node) {}

    };

    class AURA_EXPORT Input_Base : public Node_Property {
    protected:
        Output_Base *other_property = nullptr;

    public:
        Input_Base(Node &node) : Node_Property(node) {}

        virtual Type get_type() const override {
          return Type::input;
        }

        virtual Output_Base *get_other_property() const {
          return other_property;
        }

        void set_other_property(Output_Base *property) {
          other_property = property;
        }

        void set_other_property(Node *other_node);

        virtual Node *get_other_node() const {
          return other_property
                 ? &other_property->get_node()
                 : nullptr;
        }

        virtual void assign(void *data, const void *other_data, const Property &other_property)= 0;

    };

    template<typename T>
    class AURA_EXPORT Input : public Input_Base {

    public:
        Input(Node *parent) : Input_Base(*parent) {}

        virtual size_t get_size() const override {
          return sizeof(T);
        }

        void assign(void *data, const void *other_data, const Property &other_property) {
          *(T *) ((char *) data + get_offset()) = *(T *) ((char *) other_data + other_property.get_offset());
        }

    };

    template<typename T>
    class AURA_EXPORT Output : public Output_Base {

    public:
        Output(Node *parent) : Output_Base(*parent) {
        }

        virtual size_t get_size() const override {
          return sizeof(T);
        }

        virtual Type get_type() const override {
          return Type::output;
        }
    };

    class Constant_Output_Base : public Output_Base {
    public:
        Constant_Output_Base(Node *parent) : Output_Base(*parent) {}

        virtual void assign_constant(void *data)= 0;
    };

    template<typename T>
    class AURA_EXPORT Constant_Output : public Constant_Output_Base {
        T value;

    public:
        Constant_Output(T value, Node *parent) : value(value), Constant_Output_Base(parent) {}

        virtual void assign_constant(void *data) override {
          *(T *) data = value;
        }

        virtual size_t get_size() const override {
          return sizeof(T);
        }

        virtual Type get_type() const override {
          return Type::constant;
        }
    };

    class Internal_Base : public Node_Property {
    public:
        Internal_Base(Node *parent) : Node_Property(*parent) {}

        virtual void initialize_data(void *data, Producer &producer) = 0;

    };

    template<typename T>
    class AURA_EXPORT Internal : public Internal_Base {
        std::function<void(void *, Producer &)> initializer;

    public:
        Internal(Node *parent, std::function<void(void *, Producer &)> initializer) :
          Internal_Base(parent), initializer(initializer) {}

        virtual Type get_type() const override {
          return Property::Type::internal;
        }

        virtual size_t get_size() const override {
          return sizeof(T);
        }

    private:
        virtual void initialize_data(void *data, Producer &producer) override {
//          T *value = new(data) T();
          initializer(data, producer);
        }
    };
  }
}
#pragma once

#include "aura_export.h"
#include <cstdlib>
#include <stdexcept>
#include <functional>
#include <commoner/no_copy.h>
#include <memory>

namespace aura {
  class Producer;

  class Stroke;

  namespace graphing {

    class Node;

    class Node_Instance;

    class AURA_EXPORT Property : no_copy {
        friend class Node;

        friend class Node_Instance;

        std::weak_ptr<Node_Instance> node;
        size_t offset;

    protected:
//        void initialize_node(Node &node);

    public:
        enum class Type {
            output,
            input,
            constant,
            internal
        };

        virtual ~Property() {
          int k = 0;
        }

        virtual Type get_type() const = 0;
        virtual size_t get_size() const = 0;

        size_t get_offset() const {
          return offset;
        }

        const std::weak_ptr<Node_Instance> &get_node() const {
          return node;
        }
    };

    class Output_Base : public Property {
    public:

    };

    class Node_Instance;

    class AURA_EXPORT Input_Base : public Property {
    protected:
        const Output_Base *other_property = nullptr;
        std::shared_ptr<Node_Instance> other_node_instance = nullptr;

    public:
        virtual ~Input_Base() {}

        virtual Type get_type() const override {
          return Type::input;
        }

        virtual const Output_Base *get_other_property() const {
          return other_property;
        }

        void set_other_property(Output_Base *property) {
          other_property = property;
        }

//        void set_other_property(const std::shared_ptr<Node_Instance> &other_node);
        void set_other_property(const Node &other_node);

        virtual const std::weak_ptr<Node_Instance> get_other_node() const {
          return other_property
                 ? other_property->get_node()
                 : std::weak_ptr<Node_Instance>();
        }

        virtual void assign(void *data, const void *other_data, const Property &other_property)= 0;

    };

    template<typename T>
    class AURA_EXPORT Input : public Input_Base {
    public:
        Input(const Node &source) {
          set_other_property(source);

        }

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
        virtual size_t get_size() const override {
          return sizeof(T);
        }

        virtual Type get_type() const override {
          return Type::output;
        }
    };

    class Constant_Output_Base : public Output_Base {
    public:

        virtual void assign_constant(void *data) const = 0;
    };

    template<typename T>
    class AURA_EXPORT Constant_Output : public Constant_Output_Base {
        T value;

    public:
        Constant_Output(T value) : value(value) {}

        virtual ~Constant_Output() {}

        virtual void assign_constant(void *data) const override {
          *(T *) data = value;
        }

        virtual size_t get_size() const override {
          return sizeof(T);
        }

        virtual Type get_type() const override {
          return Type::constant;
        }
    };

    class Internal_Base : public Property {
    public:
        virtual void initialize_data(void *data, Producer &producer, const Stroke &) = 0;

    };

    template<typename T>
    class AURA_EXPORT Internal : public Internal_Base {
        std::function<void(void *, Producer &, const Stroke &)> initializer;

    public:
        Internal(std::function<void(void *, Producer &, const Stroke &)> initializer) :
          initializer(initializer) {}

        virtual ~Internal() {}

        virtual Type get_type() const override {
          return Property::Type::internal;
        }

        virtual size_t get_size() const override {
          return sizeof(T);
        }

    private:
        virtual void initialize_data(void *data, Producer &producer, const Stroke &stroke) override {
//          T *value = new(data) T();
          initializer(data, producer, stroke);
        }
    };
  }
}
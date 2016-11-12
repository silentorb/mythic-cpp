#pragma once

#include "Externals.h"
#include <cstdlib>
#include <stdexcept>
#include <functional>
#include <commoner/no_copy.h>
#include <memory>

namespace signal_graph {

  class Node;

  class Node_Internal;

  class Property : no_copy {
      friend class Node;

      friend class Node_Internal;

      std::weak_ptr<Node_Internal> node;
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

      const std::weak_ptr<Node_Internal> &get_node() const {
        return node;
      }

      void set_node(std::shared_ptr<Node_Internal> &value) {
        node = value;
      }

      void set_offset(size_t value) {
        offset = value;
      }
  };

  class Output_Base : public Property {
  public:

  };

  class Node_Internal;

  class Input_Base : public Property {
  protected:
      const Output_Base *other_property = nullptr;
      std::shared_ptr<Node_Internal> other_node_instance = nullptr;

      void attach(const Node &source);

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
      void set_other_property(const std::shared_ptr<Node_Internal> &other_node);

      virtual const std::weak_ptr<Node_Internal> get_other_node() const {
        return other_property
               ? other_property->get_node()
               : std::weak_ptr<Node_Internal>();
      }

      virtual void assign(void *data, const void *other_data, const Property &other_property)= 0;

  };

  template<typename T>
  class Input : public Input_Base {
  public:
      Input(const Node &source) {
        attach(source);
      }

      virtual size_t get_size() const override {
        return sizeof(T);
      }

      void assign(void *data, const void *other_data, const Property &other_property) {
        *(T *) ((char *) data + get_offset()) = *(T *) ((char *) other_data + other_property.get_offset());
      }

  };

  template<typename T>
  class Output : public Output_Base {

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
  class Constant_Output : public Constant_Output_Base {
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
      Internal_Base() {}

      virtual ~Internal_Base() {}

      virtual Type get_type() const override {
        return Property::Type::internal;
      }
  };

  template<typename T>
  class Internal : public Internal_Base {
  public:
      Internal() :
        Internal_Base() {}

      virtual size_t get_size() const override {
        return sizeof(T);
      }

  };
}
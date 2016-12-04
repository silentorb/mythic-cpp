#pragma once

#include <vector>
#include "Property.h"
#include <memory>
#include <commoner/debug-macro.h>

namespace signal_graph {

//  typedef std::function<void(void *, const Externals &)> Node_Update;
//  typedef std::function<void(void *, const Externals &)> Node_Initializer;
//  typedef std::function<void(void *)> Node_Destructor;

  template<typename Externals>
  class Node_Instance_Base : no_copy {
  public:
      Node_Instance_Base(Externals &externals) {}

      virtual ~Node_Instance_Base() {}

      virtual void const *get_data() = 0;
      virtual void update(Externals &externals) = 0;
  };

  template<typename Externals>
  class Node_Instance : public Node_Instance_Base<Externals> {
  public:
      Node_Instance(Externals &externals) : Node_Instance_Base<Externals>(externals) {}

      virtual ~Node_Instance() {}

      static Node create_node(const std::initializer_list<signal_graph::Property *> &property_initializer);
  };

  class Node_Internal : no_copy {
  public:
      Property &get_first_output() const;
      Input_Base &get_first_input() const;

      virtual int get_data_size() const = 0;
      virtual std::vector<std::unique_ptr<Property>> &get_properties()  = 0;
      virtual const std::vector<std::unique_ptr<Property>> &get_properties() const = 0;
//      virtual void update(void *data, const Externals &externals) const = 0;
//      virtual void free(void *data) const = 0;
      virtual void set_properties(const std::initializer_list<Property *> property_initializer) = 0;

      virtual void attach_input(Input_Base &input, const std::shared_ptr<Node_Internal> &instance) = 0;
      virtual void attach_output(const std::shared_ptr<Node_Internal> &instance) = 0;
      virtual const std::shared_ptr<Node_Internal> get_self() const = 0;
  };

  template<typename Externals>
  class Node_Internal_With_Properties : public Node_Internal {
      std::vector<std::unique_ptr<Property>> properties;
      std::weak_ptr<Node_Internal> self;

  public:
//      Node_Internal_With_Properties();
      Node_Internal_With_Properties(const std::initializer_list<Property *> property_initializer);

      virtual void initialize(void *data, const Externals &externals) const = 0;

      virtual std::vector<std::unique_ptr<Property>> &get_properties() override {
        return properties;
      }

      virtual const std::vector<std::unique_ptr<Property>> &get_properties() const override {
        return properties;
      }

      virtual void set_properties(const std::initializer_list<Property *> property_initializer) override;

      virtual void attach_input(Input_Base &input, const std::shared_ptr<Node_Internal> &instance) override;
      virtual void attach_output(const std::shared_ptr<Node_Internal> &instance) override;
      virtual const std::shared_ptr<Node_Internal> get_self() const override;
  };

  template<typename Externals, typename Node_Instance_Type>
  class Template_Node : public Node_Internal_With_Properties<Externals> {
  public:
      Template_Node(const std::initializer_list<Property *> &property_initializer) :
        Node_Internal_With_Properties<Externals>(property_initializer) {}

      virtual void initialize(void *data, const Externals &externals) const override {
        new(data) Node_Instance_Type(externals);
      }

      virtual void free(void *data) const override {
        ((Node_Instance_Type *) data)->~Node_Instance_Type();
      }
  };

//  template<typename Externals, typename Data_Type>
//  class Data_Node : public Template_Node<Externals> {
//  protected:
//
//  public:
//      Data_Node(const std::initializer_list<Property *> &property_initializer) :
//        Template_Node(property_initializer) {}
//
//      virtual int get_data_size() const override {
//        return sizeof(Data_Type);
//      }
//
//  };

//  class Dynamic_Node_Internal : public Node_Internal_With_Properties {
//
//#ifdef COMMONER_DEBUG
//      std::string name;
//#endif
//
//      Node_Initializer initializer;
//      Node_Update updater;
//      Node_Destructor destructor;
//
//  public:
//
//      Dynamic_Node_Internal(
//#ifdef COMMONER_DEBUG
//        const std::string &name,
//#endif
//        const Node_Initializer &initializer, const Node_Update &updater, const Node_Destructor &destructor);
//
//      Dynamic_Node_Internal(
//#ifdef COMMONER_DEBUG
//        const std::string &name,
//#endif
//        const Node_Initializer &initializer, const Node_Update &updater);
//
//      virtual void initialize(void *data, const Externals &externals) const override;
//      virtual void update(void *data, const Externals &externals) const override;
//      virtual void free(void *data) const override;
//  };
}
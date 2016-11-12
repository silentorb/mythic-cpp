#pragma once

#include <vector>
#include "Property.h"
#include <memory>
#include <commoner/debug-macro.h>

namespace signal_graph {

  typedef std::function<void(void *, const Externals &)> Node_Update;
  typedef std::function<void(void *, const Externals &)> Node_Initializer;
  typedef std::function<void(void *)> Node_Destructor;

  class Node_Internal : no_copy {

  public:
      Property &get_first_output() const;
      Input_Base &get_first_input() const;

      virtual int get_data_size() const = 0;
      virtual std::vector<std::unique_ptr<Property>> &get_properties()  = 0;
      virtual const std::vector<std::unique_ptr<Property>> &get_properties() const = 0;
      virtual void initialize(void *data, const Externals &externals) const = 0;
      virtual void update(void *data, const Externals &externals) const = 0;
      virtual void free(void *data) const = 0;
      virtual void set_properties(const std::initializer_list<Property *> property_initializer,
                                  std::shared_ptr<Node_Internal> &pointer) = 0;

      virtual void attach_input(Input_Base &input, const std::shared_ptr<Node_Internal> &instance) = 0;
      virtual void attach_output(const std::shared_ptr<Node_Internal> &instance) = 0;
  };

  class Node_Internal_With_Properties : public Node_Internal {
      std::vector<std::unique_ptr<Property>> properties;
      size_t data_size = 0;

  public:
      virtual int get_data_size() const override {
        return data_size;
      };

      virtual std::vector<std::unique_ptr<Property>> &get_properties() override {
        return properties;
      }

      virtual const std::vector<std::unique_ptr<Property>> &get_properties() const override {
        return properties;
      }

      virtual void set_properties(const std::initializer_list<Property *> property_initializer,
                                  std::shared_ptr<Node_Internal> &pointer) override;

      virtual void attach_input(Input_Base &input, const std::shared_ptr<Node_Internal> &instance) override;
      virtual void attach_output(const std::shared_ptr<Node_Internal> &instance) override;
  };

  class Dynamic_Node_Internal : public Node_Internal_With_Properties {

#ifdef COMMONER_DEBUG
      std::string name;
#endif

      Node_Initializer initializer;
      Node_Update updater;
      Node_Destructor destructor;

  public:

      Dynamic_Node_Internal(
#ifdef COMMONER_DEBUG
        const std::string &name,
#endif
        const Node_Initializer &initializer, const Node_Update &updater, const Node_Destructor &destructor);

      Dynamic_Node_Internal(
#ifdef COMMONER_DEBUG
        const std::string &name,
#endif
        const Node_Initializer &initializer, const Node_Update &updater);

      virtual void initialize(void *data, const Externals &externals) const override;
      virtual void update(void *data, const Externals &externals) const override;
      virtual void free(void *data) const override;
  };
}

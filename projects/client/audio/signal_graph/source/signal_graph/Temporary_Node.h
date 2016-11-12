#pragma once

#include <signal_graph/Node_Internal.h>

namespace signal_graph {

  class Temporary_Node : public Node_Internal {
      std::vector<Input_Base *> inputs;

  public:
      virtual int get_data_size() const override;
      virtual std::vector<std::unique_ptr<Property>> &get_properties() override;
      virtual const std::vector<std::unique_ptr<Property>> &get_properties() const override;
      virtual void initialize(void *data, const Externals &externals) const override;
      virtual void update(void *data, const Externals &externals) const override;
      virtual void free(void *data) const override;
      virtual void set_properties(const std::initializer_list<Property *> property_initializer,
                                  std::shared_ptr<Node_Internal> &pointer) override;
      virtual void attach_input(Input_Base &input, const std::shared_ptr<Node_Internal> &instance) override;
      virtual void attach_output(const std::shared_ptr<Node_Internal> &instance) override;
  };

  Node create_temporary();
}
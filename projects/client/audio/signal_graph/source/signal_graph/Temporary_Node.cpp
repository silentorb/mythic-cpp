#include "Temporary_Node.h"
#include "Node.h"

using namespace std;

namespace signal_graph {

  int Temporary_Node::get_data_size() const {
    return 0;
  }

  std::vector<std::unique_ptr<Property>> &Temporary_Node::get_properties() {
    throw runtime_error("Not supported.");
  }

  const std::vector<std::unique_ptr<Property>> &Temporary_Node::get_properties() const {
    throw runtime_error("Not supported.");
  }

  void Temporary_Node::set_properties(const std::initializer_list<Property *> property_initializer) {

  }

  void Temporary_Node::attach_input(Input_Base &input, const shared_ptr<Node_Internal> &instance) {
    inputs.push_back(&input);
		input.set_other_node(instance);
  }

  void Temporary_Node::attach_output(const std::shared_ptr<Node_Internal> &instance) {
    for (auto input: inputs) {
      input->set_other_property(instance);
    }

    // At this point this Temporary_Node should be reference counted to 0 and deleted
  }

  const shared_ptr<Node_Internal> Temporary_Node::get_self() const {
    return self.lock();
  }

  Node create_temporary() {
    return Node(shared_ptr<Node_Internal>(new Temporary_Node()));
  }
}
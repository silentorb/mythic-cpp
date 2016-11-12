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

  void Temporary_Node::initialize(void *data, const Externals &externals) const {

  }

  void Temporary_Node::update(void *data, const Externals &externals) const {

  }

  void Temporary_Node::free(void *data) const {

  }

  void Temporary_Node::set_properties(const std::initializer_list<Property *> property_initializer,
                                                    std::shared_ptr<Node_Internal> &pointer) {

  }

  void Temporary_Node::attach(Input_Base &input, const shared_ptr<Node_Internal> &instance) {

  }

  Node create_temporary() {
    return Node(shared_ptr<Node_Internal>(new Temporary_Node()));
  }
}
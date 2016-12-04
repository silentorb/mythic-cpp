#pragma once

namespace signal_graph {

  class External_Base {
      int index;

  public:
      External_Base(int index) : index(index) {}

      int get_index() const {
        return index;
      }
  };

  template<typename T>
  class External_Input : public External_Base {
  public:
      External_Input(int index) : External_Base(index) {}
  };

  template<typename T>
  class External_Output : public External_Base {
  public:
      External_Output(int index) : External_Base(index) {}
  };
}
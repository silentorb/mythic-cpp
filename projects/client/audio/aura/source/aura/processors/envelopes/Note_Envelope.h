#pragma once

#include "commoner/dllexport.h"
#include <functional>

namespace aura {

  typedef std::function<float(double)> Simple_Operator_Delegate;

  class MYTHIC_EXPORT Note_Envelope {
  public:
      virtual float get_value(double position) = 0;
  };

  class MYTHIC_EXPORT Functional_Envelope : public Note_Envelope {
      Simple_Operator_Delegate operation;
  public:

      Functional_Envelope(const Simple_Operator_Delegate &operation) : operation(operation) { }

      virtual float get_value(double position) override {
        return operation(position);
      }

  };

}

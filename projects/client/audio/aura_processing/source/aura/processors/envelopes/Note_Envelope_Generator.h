#pragma once


#include "Envelope.h"
#include "Note_Envelope.h"

namespace aura {

  class Note_Envelope_Generator {
  public:
      virtual Note_Envelope *generate_envelope() = 0;

      virtual ~Note_Envelope_Generator() { }
  };

  class Functional_Envelope_Generator : public Note_Envelope_Generator {
      Simple_Operator_Delegate operation;

  public:
      Functional_Envelope_Generator(const Simple_Operator_Delegate &operation) : operation(operation) { }

      virtual ~Functional_Envelope_Generator() { }

      virtual Note_Envelope *generate_envelope() override {
        return new Functional_Envelope(operation);
      }


  };

}
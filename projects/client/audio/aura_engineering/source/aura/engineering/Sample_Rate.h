#pragma once

namespace aura {
  namespace engineering {

    struct Sample_Rate {
    private:
        unsigned int value;

    public:
        Sample_Rate(const unsigned int &value) : value(value) {}

        unsigned int operator()() const {
          return value;
        }
    };
  }
}
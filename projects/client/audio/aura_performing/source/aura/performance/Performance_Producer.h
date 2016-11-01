#pragma once

namespace aura {
  namespace engineering {
    class Engineer;
  }

  namespace performing {

    class Performance_Producer {
    public:

        virtual engineering::Engineer &get_engineer() const = 0;
    };
  }
}
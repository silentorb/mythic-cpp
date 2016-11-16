#pragma once

class no_copy {
public:
    no_copy(no_copy const &) = delete;
    no_copy &operator=(no_copy const &) = delete;

    no_copy() { }

    no_copy(no_copy &&) { }
};

class no_copy_minimal {
public:
    no_copy_minimal &operator=(no_copy const &) = delete;
};

namespace commoner {
  class no_copy {
  public:
      no_copy(no_copy const &) = delete;
      no_copy &operator=(no_copy const &) = delete;

      no_copy() { }

      no_copy(no_copy &&) { }
  };

};
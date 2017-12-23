#pragma once



namespace glow {

  class Version {
  public:
      int major;
      int minor;
      bool ES = false;

      Version();
      Version(int major, int minor);
      bool at_least(int major, int minor);
  };
}

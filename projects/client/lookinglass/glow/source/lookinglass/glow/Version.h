#pragma once
namespace lookinglass {
  namespace glow {

    class Version {
    public:
        int major;
        int minor;
        bool ES;

        Version();
        Version(int major, int minor);
    };
  }
}
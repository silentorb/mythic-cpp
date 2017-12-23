#pragma once



namespace aura {
  namespace engineering {

    class Buffer_Manager;

    class Engineer;

    class Buffer {
        float *data;
        Buffer_Manager *manager;
        const int _size;

    public:
        Buffer(Engineer &engineer);
        Buffer(float *data, int buffer_size);
        Buffer(unsigned char *data, int buffer_size);

        ~Buffer();

        int size() {
          return _size;
        }

        float *get() const {
          return data;
        }
    };
  }
}


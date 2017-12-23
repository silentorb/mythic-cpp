#pragma once



namespace breeze {

  class Animation : no_copy {

  public:
      virtual ~Animation() {}

      virtual bool update(float delta) = 0;
      virtual void on_finish()= 0;
      virtual void* get_target() const = 0;
  };
}
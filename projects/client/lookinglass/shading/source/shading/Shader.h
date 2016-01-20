#pragma once

#include "dllexport.h"
#include "resourceful/Resource.h"
#include <string>

using namespace std;


namespace shading {

  enum Shader_Type {
      vertex = 0x8B31,
      fragment = 0x8B30
  };

  class MYTHIC_EXPORT Shader : public resourceful::Resource {
  private:
      Shader_Type type;
      string source_code;

  public:
      unsigned int id;
      Shader(Shader_Type type, string code);
      ~Shader();

      virtual void free() override;
      virtual void load() override;
  };
}

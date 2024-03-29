#pragma once

#include "resourceful/Resource.h"
#include "Shader_Type.h"
#include <string>

using namespace std;

namespace shading {

  class Shader : public resourceful::Resource {
  private:
      Shader_Type type;
      string source_code;

  public:
      unsigned int id;
      Shader(Shader_Type type, string code);
      ~Shader();

      virtual void release() override;
      virtual void load() override;

      const string &get_source_code() const {
        return source_code;
      }
  };
}

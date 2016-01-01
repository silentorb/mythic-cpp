#include "Ancient_Code_Processor.h"

namespace lookinglass {
  namespace shading {

    string olden(const string code, Shader_Type type)
    {
      string result = code;
      /*
//            code = Regex.Replace(code, @"layout\s*\(.*?\)", "");
      code = Regex.Replace(code, @"layout\s*\(.*?\)\s*uniform\s+(\w+)(\s*{.*?})\s*(\w+);", "struct $1 $2;\nuniform $1 $3;", RegexOptions.Singleline);
      code = Regex.Replace(code, @"layout\s*\(.*?\)\s*", "");
      if (type == Shader_Type.vertex)
      {
        code = Regex.Replace (code, @"^\s*in\s", "attribute ", RegexOptions.Multiline);
        code = Regex.Replace (code, @"^\s*out\s", "varying ", RegexOptions.Multiline);
      }
      else
      {
        code = Regex.Replace (code, @"^\s*in\s", "varying ", RegexOptions.Multiline);
        code = code.Replace ("out vec4 output_color;", "");
        code = code.Replace ("output_color", "gl_FragColor");
        code = Regex.Replace(code, @"texture\s*\(", "texture2D(");
      }

      return code;
       */

      return result;
    }

    string Ancient_Code_Processor::process(Shader_Type type, const string source) {
      return string("precision highp float;\n\n") + olden(source, type);
    }
  }
}
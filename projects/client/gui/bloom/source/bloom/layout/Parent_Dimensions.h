#pragma once

namespace bloom {

  struct Parent_Dimension {
//      float near;
      float length;
      bool stretches;
  };

  struct Parent_Dimensions {
      Parent_Dimension x;
      Parent_Dimension y;
  };
}
#include "Texture_From_SVG.h"

#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define NANOSVG_IMPLEMENTATION  // Expands implementation

#include "nanosvg.h"

#define NANOSVGRAST_IMPLEMENTATION

#include "nanosvgrast.h"

namespace svg {

  unsigned char *Texture_From_SVG::generate(int &width, int &height) {
//    return load_png(filename.c_str(), width, height);

    NSVGimage *image = NULL;
    NSVGrasterizer *rast = NULL;
    unsigned char *data = NULL;

    image = nsvgParseFromFile(filename.c_str(), "px", 96.0f);
    if (image == NULL) {
      throw runtime_error("Could not open SVG image.");
    }

    width = (int) image->width;
    height = (int) image->height;

    rast = nsvgCreateRasterizer();
    if (rast == NULL) {
      nsvgDelete(image);
      throw runtime_error("Could not init rasterizer.");
    }

    data = new unsigned char[width * height * 4];
    nsvgRasterize(rast, image, 0, 0, 1, data, width, height, width * 4);

//    printf("writing svg.png\n");
//    stbi_write_png("svg.png", w, h, 4, data, w * 4);

    nsvgDeleteRasterizer(rast);
    nsvgDelete(image);
    return data;
  }

}
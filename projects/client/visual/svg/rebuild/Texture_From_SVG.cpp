#include "Texture_From_SVG.h"
#include "pugixml.hpp"
#include <stdexcept>
#include <memory.h>
#include <iostream>

using namespace pugi;

namespace svg {

  unsigned char *Texture_From_SVG::generate(int &width, int &height) {
//    return load_png(filename.c_str(), width, height);

    xml_document document;

    xml_parse_result result = document.load_file(filename.c_str());
    if (!result)
      throw runtime_error(string("Error loading SVG file: ") + result.description());

      auto svg_element = document.child("svg");
      width = svg_element.attribute("width").as_int();
      height = svg_element.attribute("height").as_int();

      for (auto node: svg_element.children())
      {
          std::cout << node.name() << endl;

          for (pugi::xml_attribute attr: node.attributes())
          {
              std::cout << " " << attr.name() << "=" << attr.value();
          }

          for (pugi::xml_node child: node.children())
          {
              std::cout << ", child " << child.name();
          }

          if(node.name == "path"){

          }
          std::cout << std::endl;
      }

//    image = nsvgParseFromFile(filename.c_str(), "px", 96.0f);
//    if (image == NULL) {
//      throw runtime_error("Could not open SVG image.");
//    }
//
//    width = (int) image->width;
//    height = (int) image->height;
//
//    rast = nsvgCreateRasterizer();
//    if (rast == NULL) {
//      nsvgDelete(image);
//      throw runtime_error("Could not init rasterizer.");
//    }

    auto size = width * height * 4;
    unsigned char *data = new unsigned char[size];
    memset(data, 0, size);
    rasterize(document, width, height);
//    nsvgRasterize(rast, image, 0, 0, 1, data, width, height, width * 4);

    return data;
  }

}
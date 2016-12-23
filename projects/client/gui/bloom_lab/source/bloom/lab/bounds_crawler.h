#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include <functional>

namespace bloom {

  namespace flowers {
    class Flower;
  }

  struct Crawl_Result {
      unsigned long debug_id;
      void* pointer;
      std::string class_name;
      glm::vec2 position;
      glm::vec2 dimensions;
      std::vector<Crawl_Result> children;
  };

  void crawl(flowers::Flower *root, Crawl_Result &result);

  using Crawl_Operation = std::function<void(flowers::Flower *, int)>;
//  void crawl(flowers::Flower *root, const Crawl_Operation &operation, int depth = 0);

  using Crawl_Result_Operation= std::function<void(const Crawl_Result &, int)>;
  void process_result(const Crawl_Result &result, const Crawl_Result_Operation &operation, int depth = 0);
}
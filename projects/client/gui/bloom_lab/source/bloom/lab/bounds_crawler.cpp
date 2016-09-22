#include "bounds_crawler.h"
#include <bloom/flowers/Flower.h>
#include <bloom/flowers/Common_Flower.h>

namespace bloom {
  namespace lab {

    void crawl(flowers::Flower *root, Crawl_Result &result) {
      auto common_flower = dynamic_cast<flowers::Common_Flower *>(root);
      if (common_flower)
        result.debug_id = common_flower->debug_id;

      result.position = root->get_absolute_bounds().position;
      result.dimensions = root->get_absolute_bounds().dimensions;

      auto &children = result.children;
      for (int i = 0; i < root->get_child_count(); ++i) {
        auto child = root->get_child(i);
        children.push_back({});
        crawl(child, children[children.size() - 1]);
      }
    }

    void crawl(flowers::Flower *root, const Crawl_Operation &operation, int depth) {
      operation(root, depth);
      for (int i = 0; i < root->get_child_count(); ++i) {
        auto child = root->get_child(i);
        crawl(child, operation, depth + 1);
      }
    }

    void process_result(const Crawl_Result &result, const Crawl_Result_Operation &operation, int depth) {
      operation(result, depth);
      for (auto &child:result.children) {
        process_result(child, operation, depth + 1);
      }
    }
  }
}
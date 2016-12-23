#include "crawl_writer.h"
#include <iostream>
#include <string>

#include <bloom/lab/bounds_crawler.h>

using namespace std;
namespace bloom {

  void log_hierarchy(bloom::flowers::Flower *root) {
    Crawl_Result result;
    auto &children = result.children;
    for (int i = 0; i < root->get_child_count(); ++i) {
      auto child = root->get_child(i);
      children.push_back({});
      crawl(child, children[children.size() - 1]);
    }
    process_result(result, [](const Crawl_Result &result, int depth) {
      for (int i = 0; i < depth; ++i) {
        cout << "- ";
      }
      cout << "[" << result.class_name << "]"
           << " (" << result.position.x << ", " << result.position.y << ")"
           << " (" << result.dimensions.x << ", " << result.dimensions.y << ")"
           << " " << result.pointer
           << endl;
    });
  }

}
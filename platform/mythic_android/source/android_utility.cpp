#include "android_utility.h"
#include <stdexcept>
#include "android_native_app_glue.h"

using namespace std;

AAssetManager *utility_asset_manager;

void android_initialize_utility(AAssetManager *asset_manager) {
  utility_asset_manager = asset_manager;
}

void android_load_binary(vector<char> &buffer, const string &path) {
//  string full_path = "shaders/" + path + ".glsl";
  AAsset *asset = AAssetManager_open(utility_asset_manager, path.c_str(), AASSET_MODE_BUFFER);
  if (!asset) {
    throw std::runtime_error("Could not open asset file: " + path + ".");
  }

  auto file_size = AAsset_getLength(asset);
  buffer.resize(file_size);
//  log_info("file_size: %d", file_size);
  int count = AAsset_read(asset, buffer.data(), file_size);
//    log_info("* %d %s", count, buffer);
  if (count < 0) {
//    log_info("Error (%d) while reading  %s", count, full_path.c_str());
    throw std::runtime_error("Error while reading: " + path + ".");
  }
  AAsset_close(asset);
//  log_info("Loaded shader %s: %s", full_path.c_str(), result.c_str());
}
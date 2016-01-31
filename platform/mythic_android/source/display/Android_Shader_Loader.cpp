#include "Android_Shader_Loader.h"
#include <stdexcept>
#include "logger.h"

Android_Shader_Loader::Android_Shader_Loader(AAssetManager *asset_manager) :
  asset_manager(asset_manager) {

}

string Android_Shader_Loader::load(string path) {
  const int BUFFER_SIZE = 255;
  char buffer[BUFFER_SIZE];
  string full_path = "shaders/" + path + ".glsl";
  string result = "";
  AAsset *assetFile = AAssetManager_open(asset_manager, full_path.c_str(), AASSET_MODE_BUFFER);
  if (!assetFile) {
    throw std::runtime_error("Could not open asset file: " + full_path + ".");
  }

  int count;
  while (((count = AAsset_read(assetFile, buffer, BUFFER_SIZE)) > 0)) {
    log_info("* %d %s", count, buffer);
    result.append(buffer, count);
  }
  if (count < 0) {
    log_info("Error (%d) while reading  %s", count, full_path.c_str());
    throw std::runtime_error("Error while reading " + full_path);
  }
  AAsset_close(assetFile);
  log_info("Loaded shader %s: %s", full_path.c_str(), result.c_str());
  const char* temp = result.c_str();
  return result;
}
#include "Desktop_Shader_Loader.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <windows.h>


//std::string getexepath() {
//	char result[MAX_PATH];
////	return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
//	return std::string(result, GetCurrentDirectory(MAX_PATH, result));
//}

namespace desktop {
//	string Desktop_Shader_Loader::load(string path) {
//		ifstream file;
//		auto full_path = base_path + "/" + path + ".glsl";
////		std::replace(full_path.begin(), full_path.end(), '/', '\\');
//		auto temp = getexepath();
//
//		file.open(full_path);
//		if (!file.good())
//			throw std::runtime_error(string("Could not open ") + full_path);
//
//		stringstream stream;
//		stream << file.rdbuf();
//		return stream.str();
//	}
}
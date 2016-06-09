#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <textual/string_additions.h>
#include <memory>
#include <unistd.h>
#include <limits.h>

using namespace textual;

#ifndef SHADERS_PATH
#define SHADERS_PATH ""
#error "SHADERS_PATH must be defined externally."
#endif

#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

string load_shader(string name) {
  auto filename = STRINGIFY(SHADERS_PATH) + string("/") + name + ".glsl";
  ifstream input(filename);
  if (!input.is_open())
    throw runtime_error("Could not open " + filename);

  stringstream stream;
  stream << input.rdbuf();
  return stream.str();
}

std::string getcwd_string() {
  char buff[PATH_MAX];
  getcwd(buff, PATH_MAX);
  std::string cwd(buff);
  return cwd;
}

void write_to_file(const string &filename, const string &content) {
  ofstream myfile;
  myfile.open(filename);
  myfile << content;
}

void compare_text(const string &first, const string &second) {
  auto first2 = string_replace(first, "\r\n", "\n");
  auto second2 = string_replace(second, "\r\n", "\n");

  if (first2 != second2) {
    write_to_file("first.txt", first2);
    write_to_file("second.txt", second2);
    auto cwd = getcwd_string();
    string arguments = "/x /s "
                       + cwd + "\\first.txt "
                       + cwd + "\\second.txt ";
    auto command = "\"C:\\Program Files (x86)\\WinMerge\\WinMergeU.exe\" " + arguments;
    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe)
      throw std::runtime_error("Failed to run command.");

    while (!feof(pipe.get())) {
      if (fgets(buffer, 128, pipe.get()) != NULL)
        result += buffer;
    }
  }

  EXPECT_EQ(first2, second2);
}

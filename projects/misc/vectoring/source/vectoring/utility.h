#pragma once

#include "commoner/dllexport.h"

#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

template<typename T>
bool vector_contains(vector<T> items, T item) {
  return std::find(items.begin(), items.end(), item) != items.end();
}

template<typename T>
void vector_remove(vector<T> &items, T item) {
  items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

template<typename T>
int vector_index(vector<T> &items, T item) {
  return std::find(items.begin(), items.end(), item) - items.begin();
}

template<typename T>
T vector_first(const vector<T> &items) {
  for (auto item : items) {
    return item;
  }
    
    throw std::runtime_error("Could not find item in vector");
}
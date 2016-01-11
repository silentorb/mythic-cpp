#pragma once

#include "dllexport.h"

#include <vector>
#include <algorithm>

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
}

//template<typename T>
//class Iterable {
//    T &container;
//
//public:
//    Iterable(T &container) : container(container) { }
//
//    T::iterator begin() { return container.begin(); }
//   typename T::iterator end() { return container.end(); }
//};
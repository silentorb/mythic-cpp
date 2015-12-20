cmake_minimum_required(VERSION 3.3)

add_subdirectory(client/lookinglass/lookinglass)
add_subdirectory(lab/workshop)

add_dependencies(workshop
  lookinglass
  )
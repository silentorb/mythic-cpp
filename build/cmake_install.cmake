# Install script for directory: /Users/cj/dev/cpp/mythic

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/cj/dev/cpp/mythic/build/projects/misc/quartz/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/misc/math/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/misc/vectoring/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/generation/sculptor/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/lookinglass/glow/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/lookinglass/typography/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/lookinglass/shading/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/lookinglass/frame/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/lookinglass/through/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/lookinglass/perspective/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/lookinglass/glass/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/lookinglass/lookinglass/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/lookinglass/drawing/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/lookinglass/mesh_export/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/lookinglass/resourceful/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/scenery/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/client/main/client/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/generation/architect/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/core/mythic/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/lab/architecture_lab/cmake_install.cmake")
  include("/Users/cj/dev/cpp/mythic/build/projects/lab/lab/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/cj/dev/cpp/mythic/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

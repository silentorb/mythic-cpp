
function(print_info)
  # if you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise
  # this is the top level directory of your build tree
  MESSAGE(WARNING "CMAKE_BINARY_DIR:         " ${CMAKE_BINARY_DIR})

  # if you are building in-source, this is the same as CMAKE_CURRENT_SOURCE_DIR, otherwise this
  # is the directory where the compiled or generated files from the current CMakeLists.txt will go to
  MESSAGE(WARNING "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR})

  # this is the directory, from which cmake was started, i.e. the top level source directory
  MESSAGE(WARNING "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR})

  # this is the directory where the currently processed CMakeLists.txt is located in
  MESSAGE(WARNING "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

  # contains the full path to the top level directory of your build tree
  MESSAGE(WARNING "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})

  # contains the full path to the root of your project source directory,
  # i.e. to the nearest directory where CMakeLists.txt contains the PROJECT() command
  MESSAGE(WARNING "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})

  # set this variable to specify a common place where CMake should put all executable files
  # (instead of CMAKE_CURRENT_BINARY_DIR)
  MESSAGE(WARNING "EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH})

  # set this variable to specify a common place where CMake should put all libraries
  # (instead of CMAKE_CURRENT_BINARY_DIR)
  MESSAGE(WARNING "LIBRARY_OUTPUT_PATH:     " ${LIBRARY_OUTPUT_PATH})

  # tell CMake to search first in directories listed in CMAKE_MODULE_PATH
  # when you use FIND_PACKAGE() or INCLUDE()
  MESSAGE(WARNING "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

  # this is the complete path of the cmake which runs currently (e.g. /usr/local/bin/cmake)
  MESSAGE(WARNING "CMAKE_COMMAND: " ${CMAKE_COMMAND})

  # this is the CMake installation directory
  MESSAGE(WARNING "CMAKE_ROOT: " ${CMAKE_ROOT})

  # this is the filename including the complete path of the file where this variable is used.
  MESSAGE(WARNING "CMAKE_CURRENT_LIST_FILE: " ${CMAKE_CURRENT_LIST_FILE})

  # this is linenumber where the variable is used
  MESSAGE(WARNING "CMAKE_CURRENT_LIST_LINE: " ${CMAKE_CURRENT_LIST_LINE})

  # this is used when searching for include files e.g. using the FIND_PATH() command.
  MESSAGE(WARNING "CMAKE_INCLUDE_PATH: " ${CMAKE_INCLUDE_PATH})

  # this is used when searching for libraries e.g. using the FIND_LIBRARY() command.
  MESSAGE(WARNING "CMAKE_LIBRARY_PATH: " ${CMAKE_LIBRARY_PATH})

  # the complete system name, e.g. "Linux-2.4.22", "FreeBSD-5.4-RELEASE" or "Windows 5.1"
  MESSAGE(WARNING "CMAKE_SYSTEM: " ${CMAKE_SYSTEM})

  # the short system name, e.g. "Linux", "FreeBSD" or "Windows"
  MESSAGE(WARNING "CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME})

  # only the version part of CMAKE_SYSTEM
  MESSAGE(WARNING "CMAKE_SYSTEM_VERSION: " ${CMAKE_SYSTEM_VERSION})

  # the processor name (e.g. "Intel(R) Pentium(R) M processor 2.00GHz")
  MESSAGE(WARNING "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})

  # is TRUE on all UNIX-like OS's, including Apple OS X and CygWin
  MESSAGE(WARNING "UNIX: " ${UNIX})

  # is TRUE on Windows, including CygWin
  MESSAGE(WARNING "WIN32: " ${WIN32})

  # is TRUE on Apple OS X
  MESSAGE(WARNING "APPLE: " ${APPLE})

  # is TRUE when using the MinGW compiler in Windows
  MESSAGE(WARNING "MINGW: " ${MINGW})

  # is TRUE on Windows when using the CygWin version of cmake
  MESSAGE(WARNING "CYGWIN: " ${CYGWIN})

  # is TRUE on Windows when using a Borland compiler
  MESSAGE(WARNING "BORLAND: " ${BORLAND})

  # Microsoft compiler
  MESSAGE(WARNING "MSVC: " ${MSVC})
  MESSAGE(WARNING "MSVC_IDE: " ${MSVC_IDE})
  MESSAGE(WARNING "MSVC60: " ${MSVC60})
  MESSAGE(WARNING "MSVC70: " ${MSVC70})
  MESSAGE(WARNING "MSVC71: " ${MSVC71})
  MESSAGE(WARNING "MSVC80: " ${MSVC80})
  MESSAGE(WARNING "CMAKE_COMPILER_2005: " ${CMAKE_COMPILER_2005})


  # set this to true if you don't want to rebuild the object files if the rules have changed,
  # but not the actual source files or headers (e.g. if you changed the some compiler switches)
  MESSAGE(WARNING "CMAKE_SKIP_RULE_DEPENDENCY: " ${CMAKE_SKIP_RULE_DEPENDENCY})

  # since CMake 2.1 the install rule depends on all, i.e. everything will be built before installing.
  # If you don't like this, set this one to true.
  MESSAGE(WARNING "CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: " ${CMAKE_SKIP_INSTALL_ALL_DEPENDENCY})

  # If set, runtime paths are not added when using shared libraries. Default it is set to OFF
  MESSAGE(WARNING "CMAKE_SKIP_RPATH: " ${CMAKE_SKIP_RPATH})

  # set this to true if you are using makefiles and want to see the full compile and link
  # commands instead of only the shortened ones
  MESSAGE(WARNING "CMAKE_VERBOSE_MAKEFILE: " ${CMAKE_VERBOSE_MAKEFILE})

  # this will cause CMake to not put in the rules that re-run CMake. This might be useful if
  # you want to use the generated build files on another machine.
  MESSAGE(WARNING "CMAKE_SUPPRESS_REGENERATION: " ${CMAKE_SUPPRESS_REGENERATION})


  # A simple way to get switches to the compiler is to use ADD_DEFINITIONS().
  # But there are also two variables exactly for this purpose:

  # the compiler flags for compiling C sources
  MESSAGE(WARNING "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS})

  # the compiler flags for compiling C++ sources
  MESSAGE(WARNING "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})


  # Choose the type of build.  Example: SET(CMAKE_BUILD_TYPE Debug)
  MESSAGE(WARNING "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

  # if this is set to ON, then all libraries are built as shared libraries by default.
  MESSAGE(WARNING "BUILD_SHARED_LIBS: " ${BUILD_SHARED_LIBS})

  # the compiler used for C files
  MESSAGE(WARNING "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER})

  # the compiler used for C++ files
  MESSAGE(WARNING "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER})

  # if the compiler is a variant of gcc, this should be set to 1
  MESSAGE(WARNING "CMAKE_COMPILER_IS_GNUCC: " ${CMAKE_COMPILER_IS_GNUCC})

  # if the compiler is a variant of g++, this should be set to 1
  MESSAGE(WARNING "CMAKE_COMPILER_IS_GNUCXX : " ${CMAKE_COMPILER_IS_GNUCXX})

  # the tools for creating libraries
  MESSAGE(WARNING "CMAKE_AR: " ${CMAKE_AR})
  MESSAGE(WARNING "CMAKE_RANLIB: " ${CMAKE_RANLIB})

  #
  #MESSAGE( WARNING ": " ${} )
endfunction()

if (NOT MYTHIC_DEPENDENCIES)
  cmake_minimum_required(VERSION 3.3)
  enable_language(CXX) # SINCE Compiler/Platform variables do not normally exist before a project command in CMake.
  include(../../../cmake-tools/cmake-tools.cmake)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

create_library(metahub)

create_test(metahub_test)

set (LLVM_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/mingw/llvm)

include_directories(${LLVM_PATH}/include)

target_link_libraries(metahub_test
  ${LLVM_PATH}/lib/libLLVMCore.a
  ${LLVM_PATH}/lib/libLLVMBPFCodeGen.a
  )



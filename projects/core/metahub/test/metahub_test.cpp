#include "metahub_test.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Verifier.h"
//#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

int main(int argc, char *const argv[]) {
  Module* mod = new Module("test", getGlobalContext());
  delete mod;
  return 0;
}
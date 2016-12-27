#include "stack_trace.h"
#include <Windows.h>
#include <DbgHelp.h>
#include <memory>

using namespace std;

class Symbol_Manager {
public:
    Symbol_Manager() {
      SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_INCLUDE_32BIT_MODULES | SYMOPT_UNDNAME);
      SymInitialize(GetCurrentProcess(), nullptr, true);
    }

    ~Symbol_Manager() {
      SymCleanup(GetCurrentProcess());
    }
};

static unique_ptr<Symbol_Manager> symbol_manager;

namespace debugging {
  struct IMAGEHLP_SYMBOL64_2 : public IMAGEHLP_SYMBOL64 {
      char padding[255];
  };

  const std::string get_stack_trace(int max_frames) {
    void *stack[20];
    std::string result;
    auto process = GetCurrentProcess();
    auto count = CaptureStackBackTrace(0, max_frames, stack, nullptr);
    if(!symbol_manager.get())
      symbol_manager = unique_ptr<Symbol_Manager>(new Symbol_Manager());

    for (auto i = 0; i < count; i++) {
      ULONG64 buffer[(sizeof(SYMBOL_INFO) + 1024 + sizeof(ULONG64) - 1) / sizeof(ULONG64)] = {0};
      SYMBOL_INFO *symbol = (SYMBOL_INFO *) buffer;
      symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
      symbol->MaxNameLen = 1024;
      IMAGEHLP_LINE64 line;
      line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

      DWORD64 displacement = 0;
      DWORD displacement2 = 0;
      if (!SymFromAddr(process, DWORD64(stack[i]), &displacement, symbol))
        throw std::runtime_error("Could not load stack symbols.");

      if (!SymGetLineFromAddr64(process, DWORD64(stack[i]), &displacement2, &line))
        throw std::runtime_error("Could not load stack line numbers.");

      result.append(symbol->Name, symbol->NameLen);
      result += ":" + std::to_string(line.LineNumber) + '\n';
    }
    return result;
//		STACKFRAME64 stack;
//		CONTEXT context;
//		IMAGEHLP_SYMBOL64_2 symbol;
//		bool is_more;
//		DWORD64 displacement;
//		char name[256];
//		std::string result;
//		auto process = GetCurrentProcess();
//		auto thread = GetCurrentThread();
//
//		RtlCaptureContext(&context);
//		memset(&stack, 0, sizeof(STACKFRAME64));
//		SymInitialize(process, nullptr, false);
//
//		do {
//			is_more = StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, thread,
//				&stack, &context, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr);
//
//			symbol.SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64_2);
//			symbol.MaxNameLength = 255;
//			SymLoadModuleEx(process, nullptr, nullptr);
//			auto success = SymGetSymFromAddr64(process, static_cast<ULONG64>(stack.AddrPC.Offset), &displacement, &symbol);
//			if (!success) {
//				auto error = GetLastError();
//				LPSTR messageBuffer = nullptr;
//				size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//					nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), LPSTR(&messageBuffer), 0, nullptr);
//
//				std::string message(messageBuffer, size);
//
//				//Free the buffer.
//				LocalFree(messageBuffer);
//
//			}
//			UnDecorateSymbolName(symbol.Name, static_cast<PSTR>(name), 256, UNDNAME_COMPLETE);
//			result += name + '\n';
//
//		} while (is_more);
//
//		SymCleanup(process);
//		return result;
  }
}

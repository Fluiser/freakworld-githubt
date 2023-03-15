#include "Handlers.h"
#include <csignal>
#include <execinfo.h>
#include <iostream>

void handler_SIGSEGV(int sig)
{
    void* stack[32];
    size_t size = backtrace(stack, 32);
    std::cerr << "\nERROR " << sig << ":\n";
    char** stack_str = backtrace_symbols(stack, size);
    if(size > 0) {
        auto& stream = (std::cout << stack_str[0] << '\n');
        for(int i = 1; i < size; ++i)
            stream << stack_str[i] << '\n';
        stream << "-------------------------------";
    }
    exit(1);
}

void init_handlers()
{
    signal(SIGSEGV, handler_SIGSEGV);
}
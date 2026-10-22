#pragma once

#include <memory>
#include <cstdio>
#include <cstdlib>

#define CARROT_API

#define BIT(x) (1u<<x)

// Debug assertions: message must be a C string. Do not put side effects in condition.
#ifndef NDEBUG
#define CT_CORE_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::fprintf(stderr, "Assertion failed: %s\nMessage: %s\nLocation: %s:%d\n", \
                         #condition, (message), __FILE__, __LINE__); \
            std::fflush(stderr); \
            std::abort(); \
        } \
    } while (false)
#else
#define CT_CORE_ASSERT(condition, message) ((void)0)
#endif

namespace Carrot
{
    template<typename T>
    using Ref = std::shared_ptr<T>;
    
    template<typename T>
    using Scope = std::unique_ptr<T>;

}

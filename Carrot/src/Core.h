#pragma once

#if defined(_WIN32)
    #if defined(CARROT_BUILD_DLL)
        #define CARROT_API __declspec(dllexport)
    #else
        #define CARROT_API __declspec(dllimport)
    #endif
#else
    #define CARROT_API
#endif

#define BIT(x) (1u<<x)
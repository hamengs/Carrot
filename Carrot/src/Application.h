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

namespace Carrot
{

    class CARROT_API Application
    {
    private:
        /* data */
    public:
        Application(/* args */);
        virtual ~Application();
        void Print();
        void Run();
    };
    


} // namespace Carrot

#pragma once

#include "Core.h"

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

#pragma once
#include <fstream>
#include <sstream>

namespace Carrot
{
    class File{
    public:
        //测试读取文件代码,后期可能需要修改
        
        static std::string ReadFile(const std::string& path)
        {
            std::ifstream file(path);

            if (!file.is_open())
                throw std::runtime_error("Cannot open shader file: " + path);

            std::ostringstream contents;
            contents << file.rdbuf();

            return contents.str();
        }
    };

}
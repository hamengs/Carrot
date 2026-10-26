#include "Profiler/Profiler.h"
#include <iomanip>
#include <iostream>
#include <locale>

namespace {
    // 名字里可能出现双引号、反斜杠或换行，
    // 需要转义，才能成为合法的 JSON 字符串。
    void WriteJsonString(std::ostream& out, const std::string& text) {
        constexpr char hex[] = "0123456789abcdef";

        out << '"';

        for (unsigned char c : text) {
            switch (c) {
                case '"':  out << "\\\""; break;
                case '\\': out << "\\\\"; break;
                case '\n': out << "\\n";  break;
                case '\r': out << "\\r";  break;
                case '\t': out << "\\t";  break;

                default:
                    if (c < 0x20) {
                        out << "\\u00"
                            << hex[c >> 4]
                            << hex[c & 0x0f];
                    } else {
                        out << static_cast<char>(c);
                    }
            }
        }

        out << '"';
    }
}

namespace Carrot{


    void Profiler::StartSession(const std::string& path){
        #if CARROT_PROFILE_JSON
        EndSession();

        m_OutputStream.open(path, std::ios::out|std::ios::trunc);

        if(!m_OutputStream.is_open()){
            std::cerr << "Failed to open profile file: " << path << '\n';
            return;
        }
        // 保证小数使用小数点，并保留 double 的精度。
        m_OutputStream.imbue(std::locale::classic());
        m_OutputStream << std::setprecision(17);
        
        m_FirstEvent = true;
        m_SessionActive = true;

        m_OutputStream << "{\"traceEvents\":[";
        #endif
    }

    void Profiler::WriteProfiler(ProfilerResult& result){
        m_Results.push_back(result);
        #if CARROT_PROFILE_JSON
        if (!m_SessionActive) {
            return;
        }

        // 第一个事件前不加逗号，后面的事件前才加。
        if (!m_FirstEvent) {
            m_OutputStream << ',';
        }
        m_FirstEvent = false;

        m_OutputStream << "{\"name\":";
        WriteJsonString(m_OutputStream, result.Name);

        m_OutputStream
            << ",\"cat\":\"function\""
            << ",\"ph\":\"X\""
            << ",\"ts\":" << result.Start * 1000.0
            << ",\"dur\":" << result.Duration * 1000.0
            << ",\"pid\":0"
            << ",\"tid\":0"
            << '}';
        #endif
    }

    void Profiler::EndSession(){
        #if CARROT_PROFILE_JSON
        if (!m_SessionActive) {
            return;
        }

        m_OutputStream << "]}";
        m_OutputStream.close();

        m_SessionActive = false;
        #endif
    }
}
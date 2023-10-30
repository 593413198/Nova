
// Luhao 2023/10/31

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Noval {
    class Log {
    public:

        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){
            return s_CoreLogger;
        }

        inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){
            return s_ClientLogger;
        };

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define LOG_TRACE(...)  ::Noval::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)   ::Noval::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)   ::Noval::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)  ::Noval::Log::GetCoreLogger()->error(__VA_ARGS__)

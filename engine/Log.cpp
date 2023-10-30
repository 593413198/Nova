
// Luhao 2023/10/31

#include "Log.h"

namespace Noval {
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] [%n] %v%$");
        Log::s_CoreLogger = spdlog::stdout_color_mt("NOVAL", spdlog::color_mode::always);
        Log::s_CoreLogger->set_level(spdlog::level::trace);

        Log::s_ClientLogger = spdlog::stdout_color_mt("APP", spdlog::color_mode::always);
        Log::s_ClientLogger->set_level(spdlog::level::trace);
    }
}
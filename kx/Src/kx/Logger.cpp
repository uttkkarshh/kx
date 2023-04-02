#include "Logger.h"
namespace kx {
	   std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	   std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;
	    void Logger::Init() {
		spdlog::set_pattern("%^[T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("kx");
		s_CoreLogger ->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("app");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}


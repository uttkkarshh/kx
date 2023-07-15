#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "Core.h"

namespace kx {
	class kx_API Logger
	{
	public:
		inline static std::shared_ptr<spdlog::logger> getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger> getClientLogger() { return s_ClientLogger; }
		static void Init();

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}
#define kx_CORE_TRACE(...)  ::kx::Logger::getCoreLogger()->trace(__VA_ARGS__)
#define kx_CORE_INFO(...)   ::kx::Logger::getCoreLogger()->info(__VA_ARGS__)
#define kx_CORE_WARN(...)   ::kx::Logger::getCoreLogger()->warn(__VA_ARGS__)
#define kx_CORE_ERROR(...)  ::kx::Logger::getCoreLogger()->error(__VA_ARGS__)



//client 
#define kx_TRACE(...)	      ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define kx_INFO(...)	      ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define kx_WARN(...)	      ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define kx_ERROR(...)	      ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define kx_FATAL(...)	      ::Hazel::Log::GetClientLogger()->fatal(__VA_ARGS__)
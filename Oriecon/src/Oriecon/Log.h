#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
//#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Oriecon
{
	class ORIECON_API Log
	{
	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
		//inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		//inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
		//static std::shared_ptr<spdlog::logger> s_CoreLogger;
		//static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define ORIECON_LOG_TRACE(...) ::Oriecon::Log::GetLogger()->trace(__VA_ARGS__)
#define ORIECON_LOG_DEBUG(...) ::Oriecon::Log::GetLogger()->debug(__VA_ARGS__)
#define ORIECON_LOG_INFO(...) ::Oriecon::Log::GetLogger()->info(__VA_ARGS__)
#define ORIECON_LOG_WARN(...) ::Oriecon::Log::GetLogger()->warn(__VA_ARGS__)
#define ORIECON_LOG_ERROR(...) ::Oriecon::Log::GetLogger()->error(__VA_ARGS__)
#define ORIECON_LOG_FATAL(...) ::Oriecon::Log::GetLogger()->critical(__VA_ARGS__)

//#define CORE_LOG_TRACE(...) ::Oriecon::Log::GetCoreLogger()->trace(__VA_ARGS__)
//#define CORE_LOG_DEBUG(...) ::Oriecon::Log::GetCoreLogger()->debug(__VA_ARGS__)
//#define CORE_LOG_INFO(...) ::Oriecon::Log::GetCoreLogger()->info(__VA_ARGS__)
//#define CORE_LOG_WARN(...) ::Oriecon::Log::GetCoreLogger()->warn(__VA_ARGS__)
//#define CORE_LOG_ERROR(...) ::Oriecon::Log::GetCoreLogger()->error(__VA_ARGS__)
//#define CORE_LOG_FATAL(...) ::Oriecon::Log::GetCoreLogger()->critical(__VA_ARGS__)
//
//#define CLIENT_LOG_TRACE(...) ::Oriecon::Log::GetClientLogger()->trace(__VA_ARGS__)
//#define CLIENT_LOG_DEBUG(...) ::Oriecon::Log::GetClientLogger()->debug(__VA_ARGS__)
//#define CLIENT_LOG_INFO(...) ::Oriecon::Log::GetClientLogger()->info(__VA_ARGS__)
//#define CLIENT_LOG_WARN(...) ::Oriecon::Log::GetClientLogger()->warn(__VA_ARGS__)
//#define CLIENT_LOG_ERROR(...) ::Oriecon::Log::GetClientLogger()->error(__VA_ARGS__)
//#define CLIENT_LOG_FATAL(...) ::Oriecon::Log::GetClientLogger()->critical(__VA_ARGS__)








#include "pch.h"
#include "Log.h"

namespace Oriecon
{
	std::shared_ptr<spdlog::logger> Log::s_Logger;
	//std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	//std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_Logger = spdlog::stdout_color_mt("Oriecon");
		s_Logger->set_level(spdlog::level::level_enum::trace);

		//s_CoreLogger = spdlog::stdout_color_mt("Oriecon");
		//s_CoreLogger->set_level(spdlog::level::level_enum::trace);

		//s_ClientLogger = spdlog::stdout_color_mt("App");
		//s_ClientLogger->set_level(spdlog::level::level_enum::trace);
	}
}
#pragma once

#ifdef ORIECON_PLATFORM_WINDOWS

extern Oriecon::Application* Oriecon::CreateApplication();

int main(int argc, char** argv)
{
	Oriecon::Log::Init();
	ORIECON_LOG_INFO("Logger initialized");

	auto app = Oriecon::CreateApplication();
	app->run();
	delete app;
}

#else
#error Oriecon only support Windows
#endif
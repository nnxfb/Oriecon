#include "Oriecon.h"

class ExampleLayer : public Oriecon::Layer
{
public:
	ExampleLayer()
		: Layer("example") {}

	void onEvent(Oriecon::Event& event) override
	{
		ORIECON_LOG_TRACE("App::onEvent {0}", event.ToString());
	}
};

class Sandbox : public Oriecon::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}

private:

};

Oriecon::Application* Oriecon::CreateApplication()
{
	return new Sandbox();
}
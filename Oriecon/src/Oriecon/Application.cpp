#include "pch.h"

#include "Application.h"
#include "GLFW/glfw3.h"

namespace Oriecon {

	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		ORIECON_ASSERT(!s_Instance, "Appliaction already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::onEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->onAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->onAttach();
	}

	void Application::onEvent(Event& event)
	{
		ORIECON_LOG_TRACE("{0}", event.ToString());
		
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->onEvent(event);
			if (event.Handled)
				break;
		}
	}

	void Application::run() 
	{
		while (m_Running)
		{
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
			{
				layer->onUpdate();
			}
				

			m_Window->OnUpdate();
		}
		ORIECON_LOG_DEBUG("App stopped!");
	}

	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		ORIECON_LOG_DEBUG("Window closing...");
		m_Running = false;
		return true;
	}
}

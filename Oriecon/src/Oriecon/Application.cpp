#include "pch.h"

#include "Application.h"
#include "GLFW/glfw3.h"

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Oriecon {
	
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::onEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
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

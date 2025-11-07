#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Oriecon
{
	class ORIECON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
		void onEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool onWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}


#pragma once

#include "Core.h"
#include "Window.h"
#include "Layer/LayerStack.h"
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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool onWindowClose(WindowCloseEvent& event);

		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;

		bool m_Running = true;
	};

	Application* CreateApplication();
}


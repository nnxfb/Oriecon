#pragma once

#include "Oriecon/Core.h"
#include "Oriecon/Layer/Layer.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include "Platform/OpenGL/imgui_impl_glfw.h"

#include "Oriecon/Events/Event.h"
#include "Oriecon/Events/KeyEvent.h"
#include "Oriecon/Events/MouseEvent.h"

namespace Oriecon
{
	class ORIECON_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& event);

	private:
		bool onKeyDownEvent(KeyDownEvent& event);
		bool onKeyUpEvent(KeyUpEvent& event);
		bool onKeyTypeEvent(KeyTypeEvent& event);
		bool onMouseMoveEvent(MouseMoveEvent& event);
		bool onMouseScrollEvent(MouseScrollEvent& event);
		bool onMousePressEvent(MousePressEvent& event);
		bool onMouseReleaseEvent(MouseReleaseEvent& event);

	private:
		float m_Time = 0.0;
	};
}



#include "pch.h"
#include "ImGuiLayer.h"
#include "GLFW/glfw3.h"

#include "Oriecon/Application.h"

namespace Oriecon
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::onAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
	
		ImGui_ImplOpenGL3_Init();
	}

	void ImGuiLayer::onDetach()
	{
	}

	void ImGuiLayer::onUpdate()
	{
		Application& app = Application::Get();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (float)(time - m_Time) : 1.0f / 60.0;
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyDownEvent>(BIND_EVENT_FN(ImGuiLayer::onKeyDownEvent));
		dispatcher.Dispatch<KeyUpEvent>(BIND_EVENT_FN(ImGuiLayer::onKeyUpEvent));
		dispatcher.Dispatch<MouseMoveEvent>(BIND_EVENT_FN(ImGuiLayer::onMouseMoveEvent));
		dispatcher.Dispatch<MouseScrollEvent>(BIND_EVENT_FN(ImGuiLayer::onMouseScrollEvent));
		dispatcher.Dispatch<MousePressEvent>(BIND_EVENT_FN(ImGuiLayer::onMousePressEvent));
		dispatcher.Dispatch<MouseReleaseEvent>(BIND_EVENT_FN(ImGuiLayer::onMouseReleaseEvent));
		dispatcher.Dispatch<KeyTypeEvent>(BIND_EVENT_FN(ImGuiLayer::onKeyTypeEvent));
	}

#define KEY_INDEX(key) (key - ImGuiKey_NamedKey_BEGIN)

	bool ImGuiLayer::onKeyDownEvent(KeyDownEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey key = ImGui_ImplGlfw_KeyToImGuiKey(event.GetKeyCode(), 0);
		io.KeysData[KEY_INDEX(key)].Down = true;

		io.KeyCtrl = io.KeysData[KEY_INDEX(ImGuiKey_LeftCtrl)].Down || io.KeysData[KEY_INDEX(ImGuiKey_RightCtrl)].Down;
		io.KeyShift = io.KeysData[KEY_INDEX(ImGuiKey_LeftShift)].Down || io.KeysData[KEY_INDEX(ImGuiKey_RightShift)].Down;
		io.KeyAlt = io.KeysData[KEY_INDEX(ImGuiKey_LeftAlt)].Down || io.KeysData[KEY_INDEX(ImGuiKey_RightAlt)].Down;
		io.KeySuper = io.KeysData[KEY_INDEX(ImGuiKey_LeftSuper)].Down || io.KeysData[KEY_INDEX(ImGuiKey_RightSuper)].Down;
		return false;
	}

	bool ImGuiLayer::onKeyUpEvent(KeyUpEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey key = ImGui_ImplGlfw_KeyToImGuiKey(event.GetKeyCode(), 0);
		io.KeysData[KEY_INDEX(key)].Down = true;

		return false;
	}

	bool ImGuiLayer::onKeyTypeEvent(KeyTypeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter((unsigned int)event.GetKeyCode());
		return false;
	}

	bool ImGuiLayer::onMouseMoveEvent(MouseMoveEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetX(), event.GetY());
		return false;
	}

	bool ImGuiLayer::onMouseScrollEvent(MouseScrollEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += event.GetXOffset();
		io.MouseWheel += event.GetYOffset();
		return false;
	}

	bool ImGuiLayer::onMousePressEvent(MousePressEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetButton()] = true;
		return false;
	}

	bool ImGuiLayer::onMouseReleaseEvent(MouseReleaseEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetButton()] = false;
		return false;
	}
}


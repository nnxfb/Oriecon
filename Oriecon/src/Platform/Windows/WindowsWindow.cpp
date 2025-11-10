#include "pch.h"

#include "WindowsWindow.h"

#include "Oriecon/Events/ApplicationEvent.h"
#include "Oriecon/Events/MouseEvent.h"
#include "Oriecon/Events/KeyEvent.h"

namespace Oriecon
{
	static bool s_WindowInitialized = false;

	static void GLFWErrorFunction(int error_code, const char* description)
	{
		ORIECON_LOG_ERROR("GLFW error ({0}): {1}", error_code, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		int success;

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ORIECON_LOG_INFO("Creating window Title={0} Width={1} Height={2}", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_WindowInitialized)
		{
			success = glfwInit();
			ORIECON_ASSERT(success, "glfw initialization failed!");
			glfwSetErrorCallback(GLFWErrorFunction);
			s_WindowInitialized = true;
		}

		ORIECON_LOG_INFO("glfw initialized!");

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ORIECON_ASSERT(success, "glad initialization failed!");
		ORIECON_LOG_INFO("glad initialized!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		ORIECON_LOG_DEBUG("Setting window resize callback...");

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		ORIECON_LOG_DEBUG("Setting key callback...");

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyDownEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyDownEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyUpEvent event(key);
					data.EventCallback(event);
					break;
				}
			}
		});

		ORIECON_LOG_DEBUG("Setting key type callback...");

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypeEvent event(codepoint);
			data.EventCallback(event);
		});

		ORIECON_LOG_DEBUG("Setting mouse move callback...");

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMoveEvent event((float)xpos, (float)ypos);
			data.EventCallback(event);
		});

		ORIECON_LOG_DEBUG("Setting mouse button callback...");

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case GLFW_PRESS:
				{
					MousePressEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseReleaseEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		ORIECON_LOG_DEBUG("Setting window close callback...");

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		ORIECON_LOG_DEBUG("Setting mouse scroll callback...");

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrollEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	} 

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
			ORIECON_LOG_DEBUG("VSync enabled");
		}
		else
		{
			glfwSwapInterval(0);
			ORIECON_LOG_DEBUG("VSync disabled");
		}
		
		m_Data.VSync = enabled;
	}
}
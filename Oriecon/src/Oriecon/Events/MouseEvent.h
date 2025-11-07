#pragma once

#include "pch.h"
#include "Event.h"

namespace Oriecon
{
	class ORIECON_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse moved: " << m_MouseX << " " << m_MouseY;
			return ss.str();
		}

		CLASS_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput);
		CLASS_EVENT_TYPE(MouseMove)

	private:
		float m_MouseX, m_MouseY;
	};

	class ORIECON_API MouseScrollEvent : public Event
	{
	public:

		MouseScrollEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse scrolled: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		CLASS_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput);
		CLASS_EVENT_TYPE(MouseScroll);

	private:
		float m_XOffset, m_YOffset;
	};

	class ORIECON_API MousePressEvent : public Event
	{
	public:

		MousePressEvent(int button)
			: m_Button(button) {}

		inline int GetButton() const { return m_Button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse button " << m_Button << " pressed";
			return ss.str();
		}

		CLASS_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput);
		CLASS_EVENT_TYPE(MousePress);

	private:
		int m_Button;
	};
	
	class ORIECON_API MouseReleaseEvent : public Event
	{
	public:

		MouseReleaseEvent(int button)
			: m_Button(button) {}

		inline int GetButton() const { return m_Button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse button " << m_Button << " released";
			return ss.str();
		}

		CLASS_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput);
		CLASS_EVENT_TYPE(MouseRelease);

	private:
		int m_Button;
	};
}
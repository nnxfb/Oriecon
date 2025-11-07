#pragma once

#include "Event.h"

namespace Oriecon
{
	class ORIECON_API WindowResizeEvent : public Event
	{
	public:
		CLASS_EVENT_CATEGORY(EventCategoryWindow);
		CLASS_EVENT_TYPE(WindowResize);

		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window resized: " << m_Width << " " << m_Height;
			return ss.str();
		}

	private:
		int m_Width, m_Height;
	};

	class ORIECON_API WindowCloseEvent : public Event
	{
	public:
		CLASS_EVENT_CATEGORY(EventCategoryApp);
		CLASS_EVENT_TYPE(WindowClose);

	};

	class ORIECON_API AppUpdateEvent : public Event
	{
	public:
		CLASS_EVENT_CATEGORY(EventCategoryApp);
		CLASS_EVENT_TYPE(AppUpdate);

	};

	class ORIECON_API AppTickEvent : public Event
	{
	public:
		CLASS_EVENT_CATEGORY(EventCategoryApp);
		CLASS_EVENT_TYPE(AppTick);

	};

	class ORIECON_API AppRenderEvent : public Event
	{
	public:
		CLASS_EVENT_CATEGORY(EventCategoryApp);
		CLASS_EVENT_TYPE(AppRender);

	};
}
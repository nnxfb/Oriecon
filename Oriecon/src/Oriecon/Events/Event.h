#pragma once

#include "Oriecon/Core.h"

namespace Oriecon
{
	enum class EventType
	{
		None = 0,
		WindowCreate, WindowClose, WindowFocus, WindowLoseFocus, WindowResize, WindowMove,
		AppTick, AppUpdate, AppRender,
		KeyDown, KeyUp, KeyType,
		MousePress, MouseRelease, MouseMove, MouseScroll,
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApp = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryWindow = BIT(2),
		EventCategoryKeyboard = BIT(3),
		EventCategoryMouse = BIT(4),
		EventCategoryButton = BIT(5),
	};

#define CLASS_EVENT_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
								virtual EventType GetEventType() const override { return GetStaticType(); } \
								virtual const char* GetName() const override { return #type; }
#define CLASS_EVENT_CATEGORY(category) virtual int GetEventCategory() const override { return category; }

	class ORIECON_API Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetEventCategory() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetEventCategory() & category;
		}
		
		bool Handled = false;

	private:

	protected:

	};

	class EventDispatcher
	{
	public:
		template <typename T>
		using EventFn = std::function<bool(T&)>;

		EventDispatcher(Event& event) :
			m_Event(event) {}

		template <typename T>
		bool Dispatch(EventFn<T> fn)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = fn(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	
	private:
		Event& m_Event;
	};

	//inline std::ostream& operator<<(std::ostream& os, const Event& event)
	//{
		//return os << event.ToString();
	//}
}


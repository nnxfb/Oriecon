#pragma once

#include "Event.h"

namespace Oriecon
{
	class ORIECON_API KeyEvent : public Event
	{
	public:
		CLASS_EVENT_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

		inline int GetKeyCode() { return m_KeyCode; }

	protected:

		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class ORIECON_API KeyDownEvent : public KeyEvent
	{
	public:
		CLASS_EVENT_TYPE(KeyDown);

		KeyDownEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key pressed: " << m_KeyCode << " ( " << m_RepeatCount << ")";
			return ss.str();
		}

	private:
		unsigned int m_RepeatCount = 0;
	};

	class ORIECON_API KeyTypeEvent : public KeyEvent
	{
	public:
		CLASS_EVENT_TYPE(KeyType);

		KeyTypeEvent(int keycode)
			: KeyEvent(keycode) {}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key typed: " << m_KeyCode;
			return ss.str();
		}
	};

	class ORIECON_API KeyUpEvent : public KeyEvent
	{
	public:
		CLASS_EVENT_TYPE(KeyUp);

		KeyUpEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key released: " << m_KeyCode;
			return ss.str();
		}
	};
}
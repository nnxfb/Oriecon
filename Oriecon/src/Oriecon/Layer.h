#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Oriecon
{
	class ORIECON_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {};
		virtual void onDetach() {};
		virtual void onUpdate() {};
		virtual void onEvent(Event& event) {};

		inline const std::string& GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
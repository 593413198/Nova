
// Luhao 2023.11.18

#pragma once

#include "Event.h"

namespace Nova {

class Layer
{
public:
	Layer(const std::string& debugName) : m_DebugName(debugName) {}
	virtual ~Layer() {}

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate() {}
	virtual void OnEvent(Event& event) {}

	inline const std::string& GetName() const { return m_DebugName; }
protected:
	std::string m_DebugName;
};

}

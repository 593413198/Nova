
// Luhao 2023.11.1

#pragma once

#include "Event.h"

namespace Nova {
	
// 应用窗口的事件
class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

	unsigned int GetWidth() const { return m_Width; }
	unsigned int GetHeight() const { return m_Height; }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "WindowResizeEvent : " << m_Width << ", " << m_Height;
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResize)

private:
	unsigned int m_Width, m_Height;
};

class WindowCloseEvent : public Event {
public:
	WindowCloseEvent() = default;
	EVENT_CLASS_TYPE(WindowClose)
};

} // End Nova



// Luhao 2023.11.1

#include "Event.h"

namespace Nova {
	
// 鼠标移动事件
class MouseMovedEvent : Event {
public:
	MouseMovedEvent(const double x, const double y)
		: m_MouseX(x), m_MouseY(y)
	{}

	double GetX() const { return m_MouseX; }
	double GetY() const { return m_MouseY; }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_MouseX << "," << m_MouseY;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseMoved);

private:
	double m_MouseX, m_MouseY;
};

// 鼠标scroll事件
class MouseScrolledEvent : Event {
public:
	MouseScrolledEvent(const double x, const double y)
		: m_ScrollX(x), m_ScrollY(y)
	{}

	double GetX() const { return m_ScrollX; }
	double GetY() const { return m_ScrollY; }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << m_ScrollX << "," << m_ScrollY;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseScrolled);

private:
	double m_ScrollX, m_ScrollY;
};

} // End Nova


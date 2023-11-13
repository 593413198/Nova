
// Luhao 2023.11.1

#include "Event.h"

namespace Nova {
	
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

	const char* GetName() const override { return "WindowResizeEvent"; };

	EventType GetEventType() const override { return EventType::WindowResize; };

	//EVENT_CLASS_TYPE(WindowResize)
	//EVENT_CLASS_CATEGORY(EventCategoryApplication)

private:
	unsigned int m_Width, m_Height;
};

} // End Nova


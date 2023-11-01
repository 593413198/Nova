
// Luhao 2023.11.1

#include "Event.h"

namespace Nova {
	
class WindowEvent : public Event {

/// <summary>
/// WindowResizeEvent
/// </summary>
class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}
	unsigned int GetWidth() const { return m_Width; }
	unsigned int GetHeight() const { return m_Height; }

private:
	unsigned int m_Width, m_Height;

};



};
} // End Nova


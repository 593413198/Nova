
// Luhao 2023.11.1

#include <string.h>
#include "Event.h"

namespace Nova {
	
class KeyEvent : public Event {

public:
	KeyEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

	KeyCode GetKeyCode() const {
		return m_KeyCode;
	}

private:
	KeyCode m_KeyCode;
};


class KeyTypedEvent : public KeyEvent {
public:
	KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

};

} // End Nova

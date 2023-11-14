
// Luhao 2023.11.1

#include <string.h>
#include "Event.h"

namespace Nova {
// �����¼��Ļ��࣬����һ�� KeyCode
class KeyEvent : public Event {

public:
	KeyEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

	KeyCode GetKeyCode() const {
		return m_KeyCode;
	}

protected:
	KeyCode m_KeyCode;
};


// ���̰��µ��¼�
class KeyTypedEvent : public KeyEvent {
public:
	KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyTyped)
};

// �����ɿ����¼�
class KeyReleaseEvent : public KeyEvent {
public:
	KeyReleaseEvent(const KeyCode keycode) : KeyEvent(keycode) {}

	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyReleaseEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased)
};

// ���̳������¼�
class KeyPressedEvent : public KeyEvent {
public:
	KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
	: KeyEvent(keycode), m_IsRepeat(isRepeat)
	{}

	bool IsRepeat() const { return m_IsRepeat; }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPressed)
		
private:
	bool m_IsRepeat;
};



} // End Nova

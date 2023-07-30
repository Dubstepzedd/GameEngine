#pragma once
#include "engine/events/Event.h"
#include "engine/events/KeyCode.h"
#include <sstream>

class KeyEvent : Event {
public:
	KeyCode getKeyCode() { return m_KeyCode; };
	EVENT_CLASS_TYPE(None)
	EVENT_CATEGORY(Keyboard);
protected:
	KeyEvent(const KeyCode key) : m_KeyCode(key) {}
	KeyCode m_KeyCode;
};

class KeyPressedEvent : KeyEvent {
public:
	KeyPressedEvent(const KeyCode key, const bool isRepeat) : KeyEvent(key), m_IsRepeat(isRepeat) {

	}

	std::string toString() const override
	{
		std::stringstream ss;

		ss << "[KeyPressedEvent]: KeyCode: " << m_KeyCode << ", Repeat: " << m_IsRepeat;
		return ss.str();
	}


	EVENT_CLASS_TYPE(KeyPressed);

private:
	bool m_IsRepeat;
};

class KeyReleasedEvent : KeyEvent {

public:
	KeyReleasedEvent(const KeyCode key) : KeyEvent(key) {

	}

	std::string toString() const override
	{
		std::stringstream ss;

		ss << "[KeyReleasedEvent]: KeyCode: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased);

};

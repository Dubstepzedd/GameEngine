#pragma once
#include "engine/events/MouseCode.h"
#include "engine/events/Event.h"
#include <sstream>

class MouseButtonEvent : public Event {
public:
	MouseCode getMouseButton() const { return m_Button; }

protected:
	MouseButtonEvent(const MouseCode button)
		: m_Button(button) {}

	MouseCode m_Button;
};

class MouseButtonPressedEvent : MouseButtonEvent {
public:
	MouseButtonPressedEvent(const MouseCode button) : MouseButtonEvent(button) {

	}
	std::string toString() const override
	{
		std::stringstream ss;

		ss << "[MouseButtonPressedEvent]: MouseCode: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonPressed);

};

class MouseButtonReleasedEvent : MouseButtonEvent {
	MouseButtonReleasedEvent(const MouseCode button) : MouseButtonEvent(button) {

	}

	std::string toString() const override
	{
		std::stringstream ss;

		ss << "[MouseButtonPressedEvent]: MouseCode: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonReleased);

};

class MouseMovedEvent : Event {
public:
	MouseMovedEvent(const float x, const float y) : m_XPos(x), m_YPos(y) {
	}

	float getXPos() const {
		return m_XPos;
	}

	float getYPos() const {
		return m_YPos;
	}

	EVENT_CLASS_TYPE(MouseMoved);

private:
	float m_XPos, m_YPos;
};

class MouseScrolledEvent : Event {
public:
	MouseScrolledEvent(const float scrollAmount) : m_ScrollAmount(scrollAmount) {}
	
	float getScroll() const {
		return m_ScrollAmount;
	}

	EVENT_CLASS_TYPE(MouseScrolled);
private:
	float m_ScrollAmount;
};
#pragma once
#include "engine/events/Event.h"

class WindowResizeEvent : Event {
public:
	WindowResizeEvent(const float width, const float height) : m_Width(width), m_Height(height) {}
	
	float getWidth() const {
		return m_Width;
	}
	
	float getHeight() const {
		return m_Height;
	}

	EVENT_CLASS_TYPE(WindowResize);

private:
	float m_Height, m_Width;
};

class WindowCloseEvent : Event {
public:
	WindowCloseEvent() = default;

	EVENT_CLASS_TYPE(WindowClose)

};

class WindowMovedEvent : Event {
public:
	WindowMovedEvent(const float x, const float y) : m_XPos(x), m_YPos(y) {}

	float getX() const {
		return m_XPos;
	}

	float getY() const {
		return m_YPos;
	}

	EVENT_CLASS_TYPE(WindowMoved);
private:
	float m_XPos, m_YPos;

};

class WindowFocusEvent : Event {
public:
	WindowFocusEvent() = default;
	
	EVENT_CLASS_TYPE(WindowFocus);

};
#pragma once
#include "engine/events/Event.h"
#include <sstream>

class WindowResizeEvent : Event {
public:
	WindowResizeEvent(const int width, const int height) : m_Width(width), m_Height(height) {}
	
	int getWidth() const {
		return m_Width;
	}
	
	int getHeight() const {
		return m_Height;
	}

	std::string toString() const override
	{
		std::stringstream ss;

		ss << "[WindowResizeEvent]: Size: (" << m_Width << ", " << m_Height << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResize);
	EVENT_CATEGORY(Application);
private:
	int m_Height, m_Width;
};

class FrameBufferChangedEvent : Event {
public:
	FrameBufferChangedEvent(const int width, const int height) : m_Width(width), m_Height(height) {}

	int getWidth() const {
		return m_Width;
	}

	int getHeight() const {
		return m_Height;
	}

	std::string toString() const override
	{
		std::stringstream ss;

		ss << "[FrameBufferChangedEvent]: Size: (" << m_Width << ", " << m_Height << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(FrameBufferChanged);
	EVENT_CATEGORY(Application);
private:
	int m_Height, m_Width;
};

class WindowCloseEvent : Event {
public:
	WindowCloseEvent() = default;

	std::string toString() const override
	{
		std::stringstream ss;

		ss << "[WindowCloseEvent]: No info provided";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CATEGORY(Application);
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

	std::string toString() const override
	{
		std::stringstream ss;

		ss << "[WindowMovedEvent]: Position: (" << m_XPos << ", " << m_YPos << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowMoved);
	EVENT_CATEGORY(Application);
private:
	float m_XPos, m_YPos;

};

class WindowFocusEvent : Event {
public:
	WindowFocusEvent(const bool isFocused  = true) : m_IsFocused(isFocused) {};
	
	std::string toString() const override
	{
		std::stringstream ss;

		ss << "[WindowFocusEvent]: IsFocused: " << m_IsFocused;
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowFocus);
	EVENT_CATEGORY(Application);
private:
	bool m_IsFocused;
};
#pragma once

#include <string>

//This event structure takes huge inspiration from The Cherno's Hazel Event system. I have never built one before an decided to go for a system that I know will work. 

enum class EventType {
	None = 0,
	WindowClose, WindowFocus, WindowMoved, WindowResize,FrameBufferChanged,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled

};

enum class EventCategory {
	None = 0,
	Application, Keyboard, Mouse
};

// This macro is defined in order to reduce repeated code. It defines the type of an Event to your parameter as well as a getName method which returns the name.
#define EVENT_CLASS_TYPE(type) \
static EventType getStaticType() { return EventType::##type; } \
virtual EventType getEventType() const override { return getStaticType(); } \
virtual const char* getName() const override { return #type; }

#define EVENT_CATEGORY(category) \
virtual EventCategory getCategory() const override { return EventCategory::##category; }

class Event {
	friend class EventDispatcher; // Allows EventDispatcher to access protected/private members on Event objects.
public:
	virtual EventType getEventType() const = 0;
	virtual const char* getName() const = 0; /* For debugging purposes */
	virtual std::string toString() const { return getName(); };
	virtual EventCategory getCategory() const = 0;
protected:
	bool m_Handled = false;
};


class EventDispatcher {
public:
	EventDispatcher(Event& event) : m_Event(event) {}

	template<typename T, typename F>
	bool dispatch(F& func) {
		if (m_Event.getEventType() == T::getStaticType()) {
			m_Event.m_Handled = func(static_cast<T*>(m_Event));
			return true;
		}

		return false;
	}

private:
	Event& m_Event;

};
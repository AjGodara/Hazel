#pragma once

#include "Hazel/Core.h"
//#include <string>
//#include <functional>


namespace Hazel {

	// Currently the events in the Hazel engine are blocking, i.e., the event has to be dealt with 
	// right when it is emitted, for the future: it would make more sense to have an event bus/buffer
	// to allow the generated events to be processed during the "event" part of update stage.


	enum class EventType 
	{
		None=0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		ApplicationTick, ApplicationUpdate, ApplicationRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

	// Useful MACROS:
	// virtual GetEventType is defined so that we can get the EventType from an object/pointer of 
	// any event type.
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType(){return EventType::##type;} \
								virtual EventType GetEventType()const override {return GetStaticType();} \
								virtual const char* GetName()const override {return #type;}

#define EVENT_CLASS_CATEGORY(category)	virtual int GetCategoryFlags()const override {return category;}


	class HAZEL_API Event
	{
		friend class EventDispatcher;

	public:
		bool Handled = false;


		virtual EventType GetEventType()const = 0;
		virtual const char* GetName()const = 0;				// should it be used only for DEBUG build ?
		virtual int GetCategoryFlags()const = 0;
		virtual std::string ToString()const { return GetName(); }
		inline bool IsInCategory(EventCategory category)const { return GetCategoryFlags() & category; }

	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event): m_Event(event){}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event); // much better to use func(*(dynamic_cast<T*> &m_Event))   ???
				return true;
			}
			return false;
		}

	private:
		Event &m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}


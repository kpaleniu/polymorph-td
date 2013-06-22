#ifndef SYS_UIEVENTS_HPP_
#define SYS_UIEVENTS_HPP_

#include <gr/types.hpp>

#include <input/KeyListener.hpp>
#include <input/PointerListener.hpp>
#include <input/SurfaceListener.hpp>

#include <Event.hpp>
#include <Cpp11.hpp>

namespace polymorph { namespace sys {
namespace event {

struct KeyDown
{
	KeyDown(input::key_type key_) : key(key_) {}
	input::key_type key;
};
struct KeyUp
{
	KeyUp(input::key_type key_) : key(key_) {}
	input::key_type key;
};

struct PointerDown
{
	PointerDown(input::pointer_id id_, 
				input::pointer_button button_, 
				const gr::SurfaceVector& pointerPos_)
	:	id(id_),
		button(button_),
		pointerPos(pointerPos_)
	{}

	input::pointer_id id;
	input::pointer_button button;
	gr::SurfaceVector pointerPos;
};
struct PointerDrag
{
	PointerDrag(input::pointer_id id_, int dx_, int dy_)
	:	id(id_), dx(dx_), dy(dy_)
	{}

	input::pointer_id id;
	int dx;
	int dy;
};
struct PointerMove
{
	PointerMove(input::pointer_id id_, int dx_, int dy_)
	:	id(id_),
		dx(dx_),
		dy(dy_)
	{}

	input::pointer_id id;
	int dx;
	int dy;
};
struct PointerUp
{
	PointerUp(input::pointer_id id_, 
			  input::pointer_button button_, 
			  const gr::SurfaceVector& pointerPos_)
	:	id(id_),
		button(button_),
		pointerPos(pointerPos_)
	{}

	input::pointer_id id;
	input::pointer_button button;
	gr::SurfaceVector pointerPos;
};
struct PointerZoom
{
	PointerZoom(int dz_)
	:	dz(dz_)
	{}

	int dz;
};

struct Resize
{
	Resize(int w_, int h_) : w(w_), h(h_) {}

	int w;
	int h;
};
struct Show {};
struct Hide {};
struct Quit	{};

#ifdef NO_TEMPLATE_VARARGS_INHERIT

class UIEventManager : public 
	EventManager<event::Hide>,
	EventManager<event::KeyDown>,
	EventManager<event::KeyUp>,
	EventManager<event::PointerDown>,
	EventManager<event::PointerUp>,
	EventManager<event::PointerMove>,
	EventManager<event::PointerZoom>,
	EventManager<event::PointerDrag>,
	EventManager<event::Quit>,
	EventManager<event::Resize>,
	EventManager<event::Show>
{
public:
	template <typename ElementType>
	EventManager<ElementType>& with()
	{ return *static_cast<EventManager<ElementType>* const>(this); }

	template <typename ElementType>
	const EventManager<ElementType>& with() const
	{ return *static_cast<const EventManager<ElementType>* const>(this); }
};

#else

typedef EventManagers<event::Hide,
					 event::KeyDown,
					 event::KeyUp,
					 event::PointerDown,
					 event::PointerDrag,
					 event::PointerMove,
					 event::PointerUp,
					 event::PointerMove,
					 event::PointerZoom,
					 event::PointerDrag,
					 event::Quit,
					 event::Resize,
					 event::Show> UIEventManager;

#endif

class UIEventAdapter : public input::KeyListener,
					   public input::PointerListener,
					   public input::SurfaceListener
{
public:
	UIEventManager eventManager;

protected:
	// From KeyListener
	void onKeyDown(input::key_type key)
	{
		eventManager.with<KeyDown>().triggerEvent({key});
	}
	void onKeyUp(input::key_type key)
	{
		eventManager.with<KeyUp>().triggerEvent({key});
	}

	// From PointerListener
	void onPointerDown(input::pointer_id id, input::pointer_button button, long x, long y)
	{
		eventManager
			.with<PointerDown>()
			.triggerEvent(
				PointerDown
				(
					id,
					button,
					gr::SurfaceVector
					(
						gr::Vector2_r({gr::real_t(x), gr::real_t(y)})
					)
				));
	}
	void onPointerMove(input::pointer_id id, int dx, int dy)
	{
		eventManager.with<PointerMove>().triggerEvent({id, dx, dy});
	}
	void onPointerDrag(input::pointer_id id, int dx, int dy)
	{
		eventManager.with<PointerDrag>().triggerEvent({id, dx, dy});
	}
	void onPointerUp(input::pointer_id id, input::pointer_button button, long x, long y)
	{
		eventManager
			.with<PointerUp>()
			.triggerEvent(
				{
					id,
					button,
					gr::SurfaceVector
					(
						gr::Vector2_r({gr::real_t(x), gr::real_t(y)})
					)
				});
	}
	void onPointerZoom(int dz)
	{
		eventManager.with<PointerZoom>().triggerEvent({dz});
	}

	// From SurfaceListener
	void onResize(int w, int h)
	{
		eventManager.with<Resize>().triggerEvent({w, h});
	}
	void onShow()
	{
		eventManager.with<Show>().triggerEvent();
	}
	void onHide()
	{
		eventManager.with<Hide>().triggerEvent();
	}
	void onQuit()
	{
		eventManager.with<Quit>().triggerEvent();
	}
};

}
} }

#endif

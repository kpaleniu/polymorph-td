/**
 * @file SystemException.hpp
 *
 */

#ifndef UIEVENTS_HPP_
#define UIEVENTS_HPP_

#include <Event.hpp>

namespace sys {
namespace event {

struct KeyDown
{
	input::key_type key;
};
struct KeyUp
{
	input::key_type key;
};

struct PointerDown
{
	input::pointer_id id;
	input::pointer_button button;
	long x;
	long y;
};
struct PointerDrag
{
	input::pointer_id id;
	int dx;
	int dy;
};
struct PointerMove
{
	input::pointer_id id;
	int dx;
	int dy;
};
struct PointerUp
{
	input::pointer_id id;
	input::pointer_button button;
	long x;
	long y;
};
struct PointerZoom
{
	int dz;
};

struct Resize
{
	int w;
	int h;
};
struct Show {};
struct Hide {};
struct Quit	{};

typedef EventManagers<event::Hide,
					 event::KeyDown,
					 event::KeyUp,
					 event::PointerDown,
					 event::PointerDrag,
					 event::PointerMove,
					 event::PointerUp,
					 event::PointerZoom,
					 event::Quit,
					 event::Resize,
					 event::Show> UIEventManager;

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
		eventManager.with<KeyDown>().triggerEvent(KeyDown{key});
	}
	void onKeyUp(input::key_type key)
	{
		eventManager.with<KeyUp>().triggerEvent(KeyUp{key});
	}

	// From PointerListener
	void onPointerDown(input::pointer_id id, input::pointer_button button, long x, long y)
	{
		eventManager.with<PointerDown>().triggerEvent(PointerDown{id, button, x, y});
	}
	void onPointerMove(input::pointer_id id, int dx, int dy)
	{
		eventManager.with<PointerMove>().triggerEvent(PointerMove{id, dx, dy});
	}
	void onPointerDrag(input::pointer_id id, int dx, int dy)
	{
		eventManager.with<PointerDrag>().triggerEvent(PointerDrag{id, dx, dy});
	}
	void onPointerUp(input::pointer_id id, input::pointer_button button, long x, long y)
	{
		eventManager.with<PointerUp>().triggerEvent(PointerUp{id, button, x, y});
	}
	void onPointerZoom(int dz)
	{
		eventManager.with<PointerZoom>().triggerEvent(PointerZoom{dz});
	}

	// From SurfaceListener
	void onResize(int w, int h)
	{
		eventManager.with<Resize>().triggerEvent(Resize{w, h});
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
}

#endif

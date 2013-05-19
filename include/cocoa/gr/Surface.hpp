/**
 * @file Surface.hpp
 *
 */

#ifndef SURFACE_HPP_
#define SURFACE_HPP_

#include "gr/types.hpp"

#include <NonCopyable.hpp>
#include <Rect.hpp>

#include <memory>

namespace sys {
class Window;
}

class SurfaceImpl;


namespace gr {

/**
 *
 * TODO: Append GetLastError() information to thrown exceptions.
 */
class Surface : NonCopyable
{
public:
	Surface(sys::Window::Rect& rect);
	Surface(Surface&& surface);

	~Surface();

	/**
	 * @return true if the underlying rendering context is active in the calling thread.
	 */
	bool isActive() const;

	/**
	 * Activate/deactivate the underlying rendering context for the calling thread.
	 */
	void activate(bool activate = true);

	void flipBuffers();

	/**
	 * Gets the drawable area in window coordinates, usually from (0, 0) to window dimension.
	 */
	Rect<long> getScreenRect() const;

	ClipVector pick(const SurfaceVector& surfVec, real_t depth) const;
	SurfaceVector unPick(const ClipVector& clipVec) const;

private:
	SurfaceImpl* _impl;
};

}

#endif /* SURFACE_HPP_ */

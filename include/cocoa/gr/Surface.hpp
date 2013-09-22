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

namespace gr {

class Surface : NonCopyable
{
public:
	Surface(void* windowHandle);
	Surface(Surface&& surface);

	~Surface();
    
    void* nativeHandle() const;

	/**
	 * @return true if the underlying rendering context is active in the calling thread.
	 */
	bool isActive() const;

	
	/**
	 * Activate/deactivate the underlying rendering context for the calling thread.
	 */
	void setActive(bool activate = true);
    
	void setVSync(bool enable = true);

	void flipBuffers();

	/**
	 * Gets the drawable area in window coordinates, usually from (0, 0) to window dimension.
	 */
	Rect<long> getScreenRect() const;

	ClipVector pick(const SurfaceVector& surfVec, real_t depth) const;
	SurfaceVector unPick(const ClipVector& clipVec) const;

private:
    
    class Impl;
    std::unique_ptr<Impl> _impl;
};

}

#endif /* SURFACE_HPP_ */

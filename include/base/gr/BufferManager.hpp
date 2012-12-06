/**
 * @file BufferManager.hpp
 *
 */

#ifndef BUFFERMANAGER_HPP_
#define BUFFERMANAGER_HPP_

#include "gr/VertexBuffer.hpp"
#include "gr/IndexBuffer.hpp"
#include "gr/VertexFormat.hpp"
#include "gr/opengl.hpp"

namespace gr {

class BufferManager
{
public:
	BufferManager();
	~BufferManager();

	VertexBuffer createVertexBuffer(VertexFormat format,
	                                BufferUsage usage,
	                                size_t vertexCount,
	                                const real_t* data=nullptr);

	void setFormat(format_flags fmt);

	bool isEnabled() const;
	void disable();

private:
	format_flags _lastFmt;
};

}


#endif /* BUFFERMANAGER_HPP_ */

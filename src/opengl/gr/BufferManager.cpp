/**
 * @file BufferManager.cpp
 *
 */

#include "gr/BufferManager.hpp"

namespace gr {

BufferManager::BufferManager()
:	_lastFmt(0)
{
}

BufferManager::~BufferManager()
{
	disable();
}

void BufferManager::setFormat(format_flags fmt)
{
	if (fmt == _lastFmt)
		return;

	// If already enabled and should not be...
	format_flags disableFmt = _lastFmt & ~fmt;

	// If not enabled and should be...
	format_flags enableFmt  = ~_lastFmt & fmt;

	if ( (disableFmt &
		  format_flags(VertexFormatFlag::VERT_FLAG)) != 0 )
	{
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	else if ( (enableFmt &
			   format_flags(VertexFormatFlag::VERT_FLAG)) != 0 )
	{
		glEnableClientState(GL_VERTEX_ARRAY);
	}

	if ( (disableFmt &
		  format_flags(VertexFormatFlag::COLOR_FLAG)) != 0 )
	{
		glDisableClientState(GL_COLOR_ARRAY);
	}
	else if ( (enableFmt &
			   format_flags(VertexFormatFlag::COLOR_FLAG)) != 0 )
	{
		glEnableClientState(GL_COLOR_ARRAY);
	}

	if ( (disableFmt &
		  format_flags(VertexFormatFlag::TEXT_FLAG)) != 0 )
	{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else if ( (enableFmt &
			   format_flags(VertexFormatFlag::TEXT_FLAG)) != 0 )
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	if ( (disableFmt &
		  format_flags(VertexFormatFlag::NORMAL_FLAG)) != 0 )
	{
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	else if ( (enableFmt &
			   format_flags(VertexFormatFlag::NORMAL_FLAG)) != 0 )
	{
		glEnableClientState(GL_NORMAL_ARRAY);
	}

	_lastFmt = fmt;
}

bool BufferManager::isEnabled() const
{
	return _lastFmt != 0x00;
}

void BufferManager::disable()
{
	setFormat(0x00);
}

}



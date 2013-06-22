/**
 * @file DebugDraw.hpp
 *
 */

#include "gr/DebugDraw.hpp"

#include "gr/opengl.hpp"

namespace gr {

void DebugDraw::drawLine2D(float x1,
                           float y1,
                           float x2,
                           float y2)
{
	glBegin(GL_LINES);

	glVertex2f(x1, y1);
	glVertex2f(x2, y2);

	glEnd();
}

}

#ifndef RECT_HPP_
#define RECT_HPP_

namespace gr {

template <typename S>
class Rect
{
public:
	Rect(S left, S bottom, S width, S height);

	S getLeft() const;
	S getRight() const;
	S getBottom() const;
	S getTop() const;

	S getHeight() const;
	S getWidth() const;

	void move(S x, S y);

private:
	S _left;
	S _bottom;
	S _width;
	S _height;
};


// Implementation

template <typename S>
inline Rect<S>::Rect(S left, S bottom, S width, S height)
:	_left(left), _bottom(bottom), _width(width), _height(height)
{}

template <typename S>
inline S Rect<S>::getLeft() const
{ return _left; }

template <typename S>
inline S Rect<S>::getRight() const
{ return _left + _width; }

template <typename S>
inline S Rect<S>::getBottom() const
{ return _bottom; }

template <typename S>
inline S Rect<S>::getTop() const
{ return _bottom + _height; }

template <typename S>
inline S Rect<S>::getHeight() const
{ return _height; }

template <typename S>
inline S Rect<S>::getWidth() const
{ return _width; }

template <typename S>
inline void Rect<S>::move(S x, S y)
{ _left += x; _bottom += y; }
    
} /* namespace gr */

#endif /* RECT_HPP_ */

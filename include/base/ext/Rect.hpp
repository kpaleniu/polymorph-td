#ifndef RECT_HPP_
#define RECT_HPP_

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
	struct
	{
		S l, b, w, h;
	} _data;
};


// Implementation

template <typename S>
inline Rect<S>::Rect(S left, S bottom, S width, S height)
:	_data{left, bottom, width, height}
{}

template <typename S>
inline S Rect<S>::getLeft() const
{ return _data.l; }

template <typename S>
inline S Rect<S>::getRight() const
{ return _data.l + _data.w; }

template <typename S>
inline S Rect<S>::getBottom() const
{ return _data.b; }

template <typename S>
inline S Rect<S>::getTop() const
{ return _data.b + _data.h; }

template <typename S>
inline S Rect<S>::getHeight() const
{ return _data.h; }

template <typename S>
inline S Rect<S>::getWidth() const
{ return _data.w; }

template <typename S>
inline void Rect<S>::move(S x, S y)
{ _data.l += x; _data.b += y; }

#endif /* RECT_HPP_ */

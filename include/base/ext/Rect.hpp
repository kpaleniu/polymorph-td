/**
 * @file Any.hpp
 *
 */

#ifndef RECT_HPP_
#define RECT_HPP_

template <typename S>
class Rect
{
public:
	constexpr Rect(S left, S bottom, S width, S height);

	constexpr S getLeft() const;
	constexpr S getRight() const;
	constexpr S getBottom() const;
	constexpr S getTop() const;

	constexpr S getHeight() const;
	constexpr S getWidth() const;

	void move(S x, S y);

private:
	struct
	{
		S l, b, w, h;
	} _data;
};


// Implementation

template <typename S>
inline constexpr Rect<S>::Rect(S left, S bottom, S width, S height)
:	_data(left, bottom, width, height)
{}

template <typename S>
inline constexpr S Rect<S>::getLeft() const
{ return _data.l; }

template <typename S>
inline constexpr S Rect<S>::getRight() const
{ return _data.l + _data.w; }

template <typename S>
inline constexpr S Rect<S>::getBottom() const
{ return _data.b; }

template <typename S>
inline constexpr S Rect<S>::getTop() const
{ return _data.b + _data.h; }

template <typename S>
inline constexpr S Rect<S>::getHeight() const
{ return _data.h; }

template <typename S>
inline constexpr S Rect<S>::getWidth() const
{ return _data.w; }

template <typename S>
inline void Rect<S>::move(S x, S y)
{ _data.l += x; _data.b += y; }

#endif /* RECT_HPP_ */

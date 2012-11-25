/**
 * @file Any.hpp
 *
 */

#ifndef ANY_HPP_
#define ANY_HPP_


class AnyType
{
public:
	typedef void* pointer;

	AnyType() 				: i(0) {}
	AnyType(int i_)			: i(i_) {}
	AnyType(float f_)		: f(f_) {}
	AnyType(char c_)		: c(c_) {}
	AnyType(void* ptr_)		: ptr(ptr_) {}
	AnyType(size_t size_)	: size(size_) {}

	int& asInt()
	{ return i; }
	const int& asInt() const
	{ return i; }

	float& asFloat()
	{ return f; }
	const float& asFloat() const
	{ return f; }

	pointer& asVoidPtr()
	{ return ptr; }
	const pointer& asVoidPtr() const
	{ return ptr; }

	size_t& asSize()
	{ return size; }
	const size_t& asSize() const
	{ return size; }

	char& asChar()
	{ return c; }
	const char& asChar() const
	{ return c; }

private:

	union
	{
		int i;
		float f;
		pointer ptr;
		size_t size;
		char c;
	};
};

#endif /* ANY_HPP_ */

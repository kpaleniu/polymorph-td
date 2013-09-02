/**
 * @file Any.hpp
 *
 */

#ifndef CONDITIONAL_HPP_
#define CONDITIONAL_HPP_

#include <Assert.hpp>

#include <utility>
#include <type_traits>

template<typename T>
class Conditional
{
public:
	Conditional();
	~Conditional();

	template<typename... Args>
	void create(Args... args);

	void destroy();

	operator T();

	operator bool() const;
	bool operator!() const;

private:
	std::aligned_storage<sizeof(T), 4/*alignof(T)*/> _storage;
	bool _hasData;
};

// Implementation:

template<typename T>
Conditional<T>::Conditional()
:	_storage(),
 	_hasData(false)
{
}

template<typename T>
Conditional<T>::~Conditional()
{
	if (_hasData)
		destroy();
}

template<typename T>
template<typename... Args>
void Conditional<T>::create(Args... args)
{
	ASSERT(!_hasData, "Trying to overwrite previous data.");

	new(&_storage) T(std::forward<Args>(args)...);
	_hasData = true;
}

template<typename T>
void Conditional<T>::destroy()
{
	ASSERT(_hasData, "Trying to destroy non-existing data.");

	reinterpret_cast<T*>(&_storage)->~T();
}

template<typename T>
Conditional<T>::operator T()
{
	ASSERT(_hasData, "Trying to access uninitialized data.");

	return *reinterpret_cast<T*>(&_storage);
}

template<typename T>
Conditional<T>::operator bool() const
{
	return _hasData;
}

template<typename T>
bool Conditional<T>::operator!() const
{
	return !_hasData;
}

#endif /* CONDITIONAL_HPP_ */

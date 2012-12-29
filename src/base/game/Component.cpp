/**
 * @file Properties.cpp
 *
 */

#include "game/Component.hpp"
#include <Assert.hpp>

namespace game {

Component::Reader::Reader(const Component& comp)
:	_comp(comp)
{
}

size_t Component::Reader::getSize() const
{
	return _comp._data.size();
}

const AnyType& Component::Reader::read(int index) const
{
	return _comp._data[index];
}

Component::Writer::Writer(Component& comp)
:	_comp(comp)
{
}

size_t Component::Writer::getSize() const
{
	return _comp._data.size();
}

Component::Writer& Component::Writer::write(const AnyType& data, int index)
{
	_comp._data[index] = data;
	return *this;
}

Component::Writer& Component::Writer::write(const std::vector<AnyType>& data)
{
	ASSERT(_comp._data.size() >= data.size(), "Parameter data is too big!");

	for (size_t i = 0; i < _comp._data.size(); ++i)
		_comp._data[i] = data[i];

	return *this;
}

Component::Writer& Component::Writer::insert(const AnyType& data)
{
	_comp._data.push_back(data);
	return *this;
}

Component::Writer& Component::Writer::insert(const std::vector<AnyType>& data)
{
	_comp._data.reserve(_comp._data.size() + data.size());
	for (auto& any : data)
		_comp._data.push_back(any);

	return *this;
}

Component::Component()
:	_data()
{
}

}


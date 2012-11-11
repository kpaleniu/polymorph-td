/**
 * @file Property.hpp
 *
 */

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "concurrency/Mutex.hpp"
#include "text/util.hpp"
#include "Scoped.hpp"
#include "Any.hpp"

#include <stddef.h>
#include <map>
#include <vector>

namespace game {

typedef text::string_hash prop_type_id;

class Component
{
public:
	class Reader
	{
	public:
		Reader(const Component& comp);

		const AnyType& read(int index=0) const;

	private:
		const Component& _comp;
	};

	class Writer
	{
	public:
		Writer(Component& comp);

		Writer& write(const AnyType& data, int index=0);
		Writer& write(const std::vector<AnyType>& data);

		Writer& insert(const AnyType& data);
		Writer& insert(const std::vector<AnyType>& data);

	private:
		Component& _comp;
	};

private:
	std::vector<AnyType> _data;
};

}


#endif

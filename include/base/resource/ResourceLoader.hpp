/**
 * @file ResourceLoader.hpp
 *
 */

#ifndef RESOURCELOADER_HPP_
#define RESOURCELOADER_HPP_

#include "resource/Resource.hpp"
#include <text/util.hpp>
#include <PrivateHandle.hpp>

#include <algorithm>
#include <map>

namespace resource {

template<typename Product>
class ResourceLoader
{
private:
	struct Res
	{
		unsigned int refs;
		Product data;
	};

	typedef typename std::map<text::string_hash, Res>::iterator res_map_iterator;

public:

	class ResourceHandle : PrivateHandle<res_map_iterator>
	{
	public:
		ResourceHandle(const res_map_iterator& rmi) : PrivateHandle<res_map_iterator>(rmi)
		{ ++PrivateHandle<res_map_iterator>::_val->second.refs; }
		~ResourceHandle()
		{ --PrivateHandle<res_map_iterator>::_val->second.refs; }

		/**
		 * Returns temporary reference, valid during handle life-time.
		 */
		Product& operator*()
		{ return PrivateHandle<res_map_iterator>::_val->second.data; }

		friend class ResourceLoader<Product>;
	};

public:
	void clearGarbage();

protected:
	ResourceHandle addProduct(text::string_hash id, Product&& data);
	bool hasProduct(text::string_hash id) const;

private:
	std::map<text::string_hash, Res> _loaded;
};


// Implementation

template<typename Product>
inline void ResourceLoader<Product>::clearGarbage()
{
	// Removes all non-referenced resources.

	_loaded.erase
	(
		std::remove
		(
			_loaded.begin(),
			_loaded.end(),
			[](const std::pair<text::string_hash, Res>& v)
			{ return v.second.refs == 0; }
		)
	);
}

template<typename Product>
inline typename ResourceLoader<Product>::ResourceHandle ResourceLoader<Product>
	::addProduct(text::string_hash id, Product&& data)
{
	return ResourceHandle(std::make_pair( id, {0, std::move(data)} ));
}

template<typename Product>
inline bool ResourceLoader<Product>::hasProduct(text::string_hash id) const
{
	return _loaded.find(id) != _loaded.end();
}

}

#endif /* RESOURCELOADER_HPP_ */

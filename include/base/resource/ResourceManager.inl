
#include "resource/ResourceManager.hpp"

#include <Assert.hpp>

namespace polymorph { namespace resource {

// ResourceManager::Res

template <typename Product>
ResourceManager<Product>::Res::Res(Product&& data)
:	refs(0), data(std::move(data))
{
}

template <typename Product>
ResourceManager<Product>::Res::Res(Res&& other)
:	refs(other.refs.load()), data(std::move(other.data))
{
}


// ResourceManager::Handle

template <typename Product>
ResourceManager<Product>::Handle::Handle()
:	PrivateHandle<id_res_pointer>(nullptr)
{
}


template <typename Product>
ResourceManager<Product>::Handle::Handle(id_res_pointer dataPointer)
:	PrivateHandle<id_res_pointer>(dataPointer)
{
	if (_val != nullptr)
		++_val->second.refs;
}

template <typename Product>
ResourceManager<Product>::Handle::Handle(const Handle& other)
:	PrivateHandle<id_res_pointer>(other)
{
	if (_val != nullptr)
		++_val->second.refs;
}

template <typename Product>
ResourceManager<Product>::Handle::~Handle()
{
	if (_val != nullptr)
		--_val->second.refs;
}

template <typename Product>
Product& ResourceManager<Product>::Handle::operator*()
{
	ASSERT(_val != nullptr, "Product is null");
	return _val->second.data;
}

template <typename Product>
const Product& ResourceManager<Product>::Handle::operator*() const
{
	ASSERT(_val != nullptr, "Product is null");
	return _val->second.data;
}

template <typename Product>
Product* ResourceManager<Product>::Handle::operator->()
{
	ASSERT(_val != nullptr, "Product is null");
	return &_val->second.data;
}

template <typename Product>
const Product* ResourceManager<Product>::Handle::operator->() const
{
	ASSERT(_val != nullptr, "Product is null");
	return &_val->second.data;
}

template <typename Product>
ResourceManager<Product>::Handle::operator Product*()
{
	ASSERT(_val != nullptr, "Product is null");
	return &_val->second.data;
}

template <typename Product>
ResourceManager<Product>::Handle::operator const Product*()
{
	ASSERT(_val != nullptr, "Product is null");
	return &_val->second.data;
}

template <typename Product>
ResourceManager<Product>::Handle::operator bool()
{
	return _val != nullptr;
}

template <typename Product>
typename ResourceManager<Product>::product_id
	ResourceManager<Product>::Handle::id() const
{
	if (_val != nullptr)
		return _val->first;
	
	return 0;
}

template <typename Product>
bool ResourceManager<Product>::Handle::operator==(const Handle& other) const
{
	if (_val == nullptr || other._val == nullptr)
		return _val == other._val;

	return _val->first == other._val->first;
}

// ResourceManager

template <typename Product>
ResourceManager<Product>::ResourceManager()
:	_loaded()
{
}

template <typename Product>
ResourceManager<Product>::ResourceManager(ResourceManager&& other)
:	_loaded(std::move(other._loaded))
{
}

template <typename Product>
ResourceManager<Product>::~ResourceManager()
{
#ifdef _DEBUG
	for (const auto& idResPair : _loaded)
	{
		const Res& res = idResPair.second;
		ASSERT(res.refs == 0, "Trying to remove referenced product.");
	}
#endif
}

template <typename Product>
void ResourceManager<Product>::collectGarbage()
{
	// Removes all non-referenced resources.

	_loaded.erase
	(
		std::remove
		(
			_loaded.begin(),
			_loaded.end(),
			[](const std::pair<product_id, Res>& v)
			{ return v.second.refs == 0; }
		)
	);
}

template <typename Product>
typename ResourceManager<Product>::Handle 
	ResourceManager<Product>::add(product_id id, Product&& data)
{
	std::pair<std::map<product_id, Res>::iterator, bool> itNewPair = 
		_loaded.insert
		(
			std::make_pair
			(
				id, 
				Res(std::move(data))
			)
		);
	
	ASSERT(itNewPair.second, "Trying to re-add product.");
	return Handle( &(*itNewPair.first) );
}

template <typename Product>
const typename ResourceManager<Product>::Handle 
	ResourceManager<Product>::get(product_id id) const
{
	if (id == 0)
		return Handle();

	return Handle( &(*_loaded.find(id)) );
}

template <typename Product>
typename ResourceManager<Product>::Handle
ResourceManager<Product>::get(product_id id)
{
	if (id == 0)
		return Handle();

	return Handle(&(*_loaded.find(id)));
}

template <typename Product>
bool ResourceManager<Product>::has(product_id id) const
{
	return _loaded.find(id) != _loaded.end();
}

} }

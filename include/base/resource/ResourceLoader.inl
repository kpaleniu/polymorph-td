
#include "resource/ResourceLoader.hpp"

#include <Assert.hpp>

namespace resource {

// ResourceLoader::Res

template <typename Product>
ResourceLoader<Product>::Res::Res(Product&& data)
:	refs(0), data(std::move(data))
{
}

template <typename Product>
ResourceLoader<Product>::Res::Res(Res&& other)
:	refs(other.refs), data(std::move(other.data))
{
}


// ResourceLoader::ResourceHandle

template <typename Product>
ResourceLoader<Product>::ResourceHandle::ResourceHandle()
:	PrivateHandle<res_pointer>(nullptr)
{
}

template <typename Product>
ResourceLoader<Product>::ResourceHandle::ResourceHandle(res_pointer dataPointer)
:	PrivateHandle<res_pointer>(dataPointer)
{
	ASSERT(_val != nullptr, "Product is null");
	++_val->refs;
}

template <typename Product>
ResourceLoader<Product>::ResourceHandle::ResourceHandle(const ResourceHandle& other)
:	PrivateHandle<res_pointer>(other)
{
	if (_val != nullptr)
		++_val->refs;
}

template <typename Product>
ResourceLoader<Product>::ResourceHandle::~ResourceHandle()
{
	if (_val != nullptr)
		--_val->refs;
}

template <typename Product>
Product& ResourceLoader<Product>::ResourceHandle::operator*()
{
	ASSERT(_val != nullptr, "Product is null");
	return _val->data;
}

template <typename Product>
const Product& ResourceLoader<Product>::ResourceHandle::operator*() const
{
	ASSERT(_val != nullptr, "Product is null");
	return _val->data;
}

template <typename Product>
Product* ResourceLoader<Product>::ResourceHandle::operator->()
{
	ASSERT(_val != nullptr, "Product is null");
	return &_val->data;
}

template <typename Product>
const Product* ResourceLoader<Product>::ResourceHandle::operator->() const
{
	ASSERT(_val != nullptr, "Product is null");
	return &_val->data;
}

template <typename Product>
ResourceLoader<Product>::ResourceHandle::operator Product*()
{
	ASSERT(_val != nullptr, "Product is null");
	return &_val->data;
}

template <typename Product>
ResourceLoader<Product>::ResourceHandle::operator const Product*()
{
	ASSERT(_val != nullptr, "Product is null");
	return &_val->data;
}

template <typename Product>
ResourceLoader<Product>::ResourceHandle::operator bool()
{
	return _val != nullptr;
}

// ResourceLoader

template <typename Product>
inline void ResourceLoader<Product>::collectGarbage()
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

template <typename Product>
inline typename ResourceLoader<Product>::ResourceHandle 
	ResourceLoader<Product>::addProduct(text::string_hash id, Product&& data)
{
	std::pair<std::map<text::string_hash, Res>::iterator, bool> itNewPair = 
		_loaded.insert
		(
			std::make_pair
			(
				id, 
				Res(std::move(data))
			)
		);
	
	ASSERT(itNewPair.second, "Trying to re-add product.");
	return ResourceHandle(&itNewPair.first->second);
}

template <typename Product>
inline typename ResourceLoader<Product>::ResourceHandle ResourceLoader<Product>
	::getProduct(text::string_hash id)
{
	return &_loaded.find(id)->second;
}


template <typename Product>
inline bool ResourceLoader<Product>::hasProduct(text::string_hash id) const
{
	return _loaded.find(id) != _loaded.end();
}

}

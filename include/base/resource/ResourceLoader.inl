
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
:	PrivateHandle<id_res_pointer>(nullptr)
{
}


template <typename Product>
ResourceLoader<Product>::ResourceHandle::ResourceHandle(id_res_pointer dataPointer)
:	PrivateHandle<id_res_pointer>(dataPointer)
{
	if (_val != nullptr)
		++this->_val->second.refs;
}

template <typename Product>
ResourceLoader<Product>::ResourceHandle::ResourceHandle(const ResourceHandle& other)
:	PrivateHandle<id_res_pointer>(other)
{
	if (this->_val != nullptr)
		++this->_val->second.refs;
}

template <typename Product>
ResourceLoader<Product>::ResourceHandle::~ResourceHandle()
{
	if (this->_val != nullptr)
		--this->_val->second.refs;
}

template <typename Product>
Product& ResourceLoader<Product>::ResourceHandle::operator*()
{
	ASSERT(this->_val != nullptr, "Product is null");
	return this->_val->second.data;
}

template <typename Product>
const Product& ResourceLoader<Product>::ResourceHandle::operator*() const
{
	ASSERT(this->_val != nullptr, "Product is null");
	return this->_val->second.data;
}

template <typename Product>
Product* ResourceLoader<Product>::ResourceHandle::operator->()
{
	ASSERT(this->_val != nullptr, "Product is null");
	return &this->_val->second.data;
}

template <typename Product>
const Product* ResourceLoader<Product>::ResourceHandle::operator->() const
{
	ASSERT(this->_val != nullptr, "Product is null");
	return &this->_val->second.data;
}

template <typename Product>
ResourceLoader<Product>::ResourceHandle::operator Product*()
{
	ASSERT(this->_val != nullptr, "Product is null");
	return &this->_val->second.data;
}

template <typename Product>
ResourceLoader<Product>::ResourceHandle::operator const Product*()
{
	ASSERT(this->_val != nullptr, "Product is null");
	return &this->_val->second.data;
}

template <typename Product>
ResourceLoader<Product>::ResourceHandle::operator bool()
{
	return this->_val != nullptr;
}

template <typename Product>
text::string_hash ResourceLoader<Product>::ResourceHandle::id() const
{
	if (this->_val != nullptr)
		return this->_val->first;
	else
		return 0;
}

template <typename Product>
bool ResourceLoader<Product>::ResourceHandle::operator==(const ResourceHandle& other) const
{
	if (_val == nullptr || other._val == nullptr)
		return this->_val == other._val;

	return this->_val->first == other._val->first;
}

// ResourceLoader

template <typename Product>
ResourceLoader<Product>::ResourceLoader()
:	_loaded()
{
}

template <typename Product>
ResourceLoader<Product>::ResourceLoader(ResourceLoader&& other)
:	_loaded(std::move(other._loaded))
{
}

template <typename Product>
ResourceLoader<Product>::~ResourceLoader()
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
	std::pair<typename std::map<text::string_hash, Res>::iterator, bool> itNewPair =
		_loaded.insert
		(
			std::make_pair
			(
				id, 
				Res(std::move(data))
			)
		);
	
	ASSERT(itNewPair.second, "Trying to re-add product.");
	return ResourceHandle( &(*itNewPair.first) );
}

template <typename Product>
inline typename ResourceLoader<Product>::ResourceHandle ResourceLoader<Product>
	::getProduct(text::string_hash id) const
{
	if (id == 0)
		return ResourceHandle();

	return ResourceHandle( &(*_loaded.find(id)) );
}


template <typename Product>
inline bool ResourceLoader<Product>::hasProduct(text::string_hash id) const
{
	return _loaded.find(id) != _loaded.end();
}

}

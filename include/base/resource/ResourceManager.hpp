#pragma once

#include "resource/Resource.hpp"

#include <PrivateHandle.hpp>
#include <NonCopyable.hpp>

#include <algorithm>
#include <map>
#include <atomic>

namespace polymorph { namespace resource {

/**
 * Class ResourceManager, collection of reference counted named products.
 *
 * This class offers direct reference (constant time access) to a product
 * through the Handle interface.
 *
 *
 * THREAD SAFETY NOTES:
 *
 * Getting and checking for existance is thread safe, collecting garbage
 * is thread safe as long as the Products destructor is as well.
 *
 * Modyfying different products from its handle is thread safe if the
 * Product's modification is thread safe.
 *
 * Adding Products concurrently is not expected to be thread safe. Use
 * only one thread to add Products.
 */
template <typename Product>
class ResourceManager : NonCopyable
{
public:
	typedef typename std::size_t product_id;

private:
	class Res : NonCopyable
	{
	public:
		Res(Product&& data);
		Res(Res&& res);

		std::atomic<unsigned int> refs;
		Product data;
	};

	
	typedef typename std::map<product_id, Res>::pointer id_res_pointer;
public:

	class Handle : PrivateHandle<id_res_pointer>
	{
	public:
		Handle();
		Handle(id_res_pointer resPtr);
		Handle(const Handle& other);
		~Handle();

		Product& operator*();
		const Product& operator*() const;

		Product* operator->();
		const Product* operator->() const;

		operator Product*();
		operator const Product*();

		operator bool();

		product_id id() const;

		bool operator==(const Handle& other) const;

		friend class ResourceManager<Product>;
	};

public:
	ResourceManager();
	ResourceManager(ResourceManager&& other);
	~ResourceManager();

	void collectGarbage();

	Handle add(product_id id, Product&& data);
	
	Handle get(product_id id);
	const Handle get(product_id id) const;
	
	bool has(product_id id) const;

private:

	// Getting products will mutate Res member.
	//
	// NOTE: If you change this, make sure the thread safety 
	//       quarantee still applies.
	mutable std::map<product_id, Res> _loaded;
};

}  }

#include "resource/ResourceManager.inl"

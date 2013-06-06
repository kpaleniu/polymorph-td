/**
 * @file ResourceLoader.hpp
 *
 */

#ifndef RESOURCELOADER_HPP_
#define RESOURCELOADER_HPP_

#include "resource/Resource.hpp"

#include <text/util.hpp>

#include <PrivateHandle.hpp>
#include <NonCopyable.hpp>

#include <algorithm>
#include <map>

namespace resource {

template <typename Product>
class ResourceLoader : NonCopyable
{
private:
	class Res : NonCopyable
	{
	public:
		Res(Product&& data);
		Res(Res&& res);

		unsigned int refs;
		Product data;

	};

	typedef Res* res_pointer;

public:

	class ResourceHandle : PrivateHandle<res_pointer>
	{
	public:
		ResourceHandle();
		ResourceHandle(res_pointer resPtr);
		ResourceHandle(const ResourceHandle& other);
		~ResourceHandle();

		// Returns temporary reference, valid during handle life-time:
		Product& operator*();
		const Product& operator*() const;

		Product* operator->();
		const Product* operator->() const;

		operator Product*();
		operator const Product*();
		//

		friend class ResourceLoader<Product>;
	};

public:
	void collectGarbage();

protected:
	ResourceHandle addProduct(text::string_hash id, Product&& data);
	ResourceHandle getProduct(text::string_hash id);
	bool hasProduct(text::string_hash id) const;

private:
	std::map<text::string_hash, Res> _loaded;
};

}

#include "resource/ResourceLoader.inl"

#endif /* RESOURCELOADER_HPP_ */

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

	typedef typename std::map<text::string_hash, Res>::pointer id_res_pointer;

public:

	class ResourceHandle : PrivateHandle<id_res_pointer>
	{
	public:
		ResourceHandle();
		ResourceHandle(id_res_pointer resPtr);
		ResourceHandle(const ResourceHandle& other);
		~ResourceHandle();

		Product& operator*();
		const Product& operator*() const;

		Product* operator->();
		const Product* operator->() const;

		operator Product*();
		operator const Product*();

		operator bool();

		text::string_hash id() const;

		bool operator==(const ResourceHandle& other) const;

		friend class ResourceLoader<Product>;
	};

public:
	void collectGarbage();

protected:
	ResourceHandle addProduct(text::string_hash id, Product&& data);
	ResourceHandle getProduct(text::string_hash id) const;
	bool hasProduct(text::string_hash id) const;

private:

	// Getting products will mutate Res member.
	mutable std::map<text::string_hash, Res> _loaded;
};

}

#include "resource/ResourceLoader.inl"

#endif /* RESOURCELOADER_HPP_ */



#ifndef TEMPLATE_UTIL_HPP_
#define TEMPLATE_UTIL_HPP_

template<typename CustomType, typename... Args>
class InheritanceIterator;

template<typename CustomType, typename Head, typename... Args>
class InheritanceIterator<CustomType, Head, Args...>
:	public InheritanceIterator<CustomType, Args...>,
 	public CustomType::template type<Head>
{
public:
	using InheritanceIterator<CustomType, Args...>::with;
	typedef typename CustomType::template type<Head> HeadType;

	HeadType& with() { return *static_cast<HeadType*>(this); }
};

template<typename CustomType, typename Head>
class InheritanceIterator<CustomType, Head>
:	public CustomType::template type<Head>
{
public:
	typedef typename CustomType::template type<Head> HeadType;

	HeadType& with() { return *static_cast<HeadType*>(this); }
};

#endif

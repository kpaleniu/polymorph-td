

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
	typedef InheritanceIterator<CustomType, Args...> ParentType;
	typedef InheritanceIterator<CustomType, Head, Args...> ThisType;
	typedef typename CustomType::template type<Head> HeadType;

	// Recursive methods

	InheritanceIterator() = default;

	InheritanceIterator(const ThisType& other)
	:	ParentType(static_cast<const ParentType&>(other)),
	 	HeadType(static_cast<const HeadType&>(other))
	{
	}

	ThisType& operator=(const ThisType& other)
	{
		static_cast<HeadType&>(*this) = static_cast<const HeadType&>(other);
		static_cast<ParentType&>(*this) = static_cast<const ParentType&>(other);

		return *this;
	}
};

template<typename CustomType, typename Head>
class InheritanceIterator<CustomType, Head>
:	public CustomType::template type<Head>
{
public:
	typedef InheritanceIterator<CustomType, Head> ThisType;
	typedef typename CustomType::template type<Head> HeadType;

	// Recursive methods tail

	ThisType& operator=(const ThisType& other)
	{
		static_cast<HeadType&>(*this) = static_cast<const HeadType&>(other);

		return *this;
	}
};



#endif

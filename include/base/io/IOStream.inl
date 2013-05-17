
#include <type_traits>

namespace io {

template <typename TriviallyCopyable>
InputStream& InputStream::operator>>(TriviallyCopyable& data)
{
	read(&data, 
		 std::alignment_of<TriviallyCopyable>::value,
		 sizeof(TriviallyCopyable), 
		 1);
	
	return *this;
}

template <typename TriviallyCopyable>
InputStream& InputStream::readBlock(TriviallyCopyable& data, std::size_t size)
{
	read(&data, 
		 std::alignment_of<TriviallyCopyable>::value, 
		 sizeof(TriviallyCopyable), 
		 size);

	return *this;
}

template <typename TriviallyCopyable>
OutputStream& OutputStream::operator<<(const TriviallyCopyable& data)
{
	write(&data, 
		  std::alignment_of<TriviallyCopyable>::value,
		  sizeof(TriviallyCopyable), 
		  1);
	
	return *this;
}

template <typename TriviallyCopyable>
OutputStream& OutputStream::operator<<(const std::pair<const TriviallyCopyable&, std::size_t>& dataCollection)
{
	write(&dataCollection.first, 
		  std::alignment_of<TriviallyCopyable>::value, 
		  sizeof(TriviallyCopyable), 
		  dataCollection.second);

	return *this;
}

}
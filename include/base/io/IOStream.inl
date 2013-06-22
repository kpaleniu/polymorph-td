
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
InputStream& InputStream::readBlock(TriviallyCopyable* data, std::size_t count)
{
	read(data, 
		 std::alignment_of<TriviallyCopyable>::value, 
		 sizeof(TriviallyCopyable), 
		 count);

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
OutputStream& OutputStream::writeBlock(const TriviallyCopyable* data, std::size_t count)
{
	write(data, 
		  std::alignment_of<TriviallyCopyable>::value, 
		  sizeof(TriviallyCopyable), 
		  count);

	return *this;
}

}
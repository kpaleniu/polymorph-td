#ifndef ALIGNMENT_HPP_
#define ALIGNMENT_HPP_

#include <memory>

/**
 * If data pointer isn't aligned according to first parameter,
 * then the pointer is incremented to the next aligned pointer,
 * else the second parameter is returned.
 *
 * @param typeAlignment	The required alignment of return value,
 *						must be power of 2.
 * @param data			A pointer to align.
 * @return				First aligned pointer greater or equal 
 *						to data.
 */
void* align(std::size_t typeAlignment, const void* data);

#endif
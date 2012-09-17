/*
 * @file Time.hpp
 */

#ifndef NONCOPYABLE_HPP_
#define NONCOPYABLE_HPP_


class NonCopyable {
protected:
	NonCopyable()  {}
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable&);                  // = delete;
	const NonCopyable& operator=(const NonCopyable&); // = delete;
};

#endif /* NONCOPYABLE_HPP_ */

#pragma once

#include <string>
#include <memory>

inline std::size_t hash(const std::string& val)
{
	static std::hash<std::string> hash_fn;

	return hash_fn(val);
}
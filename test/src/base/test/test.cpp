#include "test/test.hpp"

#include <vector>
#include <iostream>

namespace test {

namespace {

std::vector<std::pair<std::string, Test>> s_tests;

}

void addTest(const std::string& testName, const Test& test)
{
	s_tests.push_back(std::make_pair(testName, test));
}

int runTests()
{
	int i = 0;

	for (auto& testPair : s_tests)
	{
		try
		{
			std::cout << "Running test " << testPair.first.c_str();
			testPair.second();
			std::cout << " success";
		}
		catch (Failed& e)
		{
			++i;
			std::cout << " fails " << e.what();
		}
		catch (CannotRun& e)
		{
			std::cout << " cannot run" << e.what();
		}
		catch (std::exception& e)
		{
			std::cout << " unexpected exception: " << e.what();
			++i;
		}
		catch (...)
		{
			std::cout << " unexpected exception.";
			++i;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Success: " << (s_tests.size() - i) << '/' << s_tests.size() << std::endl;

	return i;
}

}
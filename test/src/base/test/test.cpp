#include "test/test.hpp"

#include <map>
#include <iostream>

namespace test {

namespace {

std::map<std::string, Test> s_tests;

}

void addTest(const std::string& testName, const Test& test)
{
	s_tests[testName] = test;
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
		catch (Failed&)
		{
			++i;
			std::cout << " fails";
		}
		catch (CannotRun&)
		{
			std::cout << " cannot run";
		}
		catch (std::exception& e)
		{
			std::cout << " unexpected exception: " << e.what();
			++i;
		}
		catch (...)
		{
			std::cout << " unexpected exception";
			++i;
		}
		std::cout << std::endl;
	}

	return i;
}

}
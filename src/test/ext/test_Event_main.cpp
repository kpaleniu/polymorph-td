#include "Event.hpp"

#include <iostream>

using namespace std;

struct E1
{
	int a;
};

struct E2
{
	int a, b;
};

struct E3
{
	int a, b, c;
};

struct FuckUp
{};

int main(int argc, char* argv[])
{
	EventManager<E1, E2, E3> manager1;

	// auto& fuckUpManager = manager1.as<FuckUp>(); // Invalid cast build error.

	auto& e1Bindings = manager1.as<E1>().actionBindings();
	auto& e2Bindings = manager1.as<E2>().actionBindings();
	auto& e3Bindings = manager1.as<E3>().actionBindings();

	e1Bindings.push_back([](const E1& e1)
	{
		cout << "E1: " << e1.a << endl;
	});
	e2Bindings.push_back([](const E2& e2)
	{
		cout << "E2: " << e2.a << " " << e2.b << endl;
	});
	e3Bindings.push_back([](const E3& e3)
	{
		cout << "E3: " << e3.a << " " << e3.b << " " << e3.c << endl;
	});

	manager1.as<E1>().triggerEvent(E1{1});
	manager1.as<E2>().triggerEvent(E2{1, 2});
	manager1.as<E3>().triggerEvent(E3{1, 2, 3});

	EventManager<E1, E2, E3> manager2;

	manager2 = manager1;

	manager2.as<E1>().triggerEvent(E1{1});
	manager2.as<E2>().triggerEvent(E2{1, 2});
	manager2.as<E3>().triggerEvent(E3{1, 2, 3});

	auto foo = [=]()
	{
		auto manager3 = manager2;
		manager3.as<E1>().triggerEvent(E1{1});
		manager3.as<E2>().triggerEvent(E2{1, 2});
		manager3.as<E3>().triggerEvent(E3{1, 2, 3});
	};

	foo();

	EventManager<E1, E2, E3> manager4(manager2);

	cout << "===" << endl;

	manager4.as<E1>().triggerEvent(E1{1});
	manager4.as<E2>().triggerEvent(E2{1, 2});
	manager4.as<E3>().triggerEvent(E3{1, 2, 3});

	return 0;
}

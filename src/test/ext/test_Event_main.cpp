#include "Event.hpp"

#include <iostream>

using namespace std;

struct E
{};

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
	EventManagers<E, E1, E2, E3> manager1;

	// auto& fuckUpManager = manager1.with<FuckUp>(); // Invalid cast build error.

	auto& eBindings = manager1.with<E>().actionBindings();
	auto& e1Bindings = manager1.with<E1>().actionBindings();
	auto& e2Bindings = manager1.with<E2>().actionBindings();
	auto& e3Bindings = manager1.with<E3>().actionBindings();

	eBindings.push_back([]
	{
		cout << "E" << endl;
	});

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

	manager1.with<E>().triggerEvent();
	manager1.with<E1>().triggerEvent(E1{1});
	manager1.with<E2>().triggerEvent(E2{1, 2});
	manager1.with<E3>().triggerEvent(E3{1, 2, 3});

	// manager1.with<E>().triggerEvent(E{}); // Build error (expects 0 arguments).

	EventManagers<E, E1, E2, E3> manager2;

	manager2 = manager1;

	manager2.with<E>().triggerEvent();
	manager2.with<E1>().triggerEvent(E1{1});
	manager2.with<E2>().triggerEvent(E2{1, 2});
	manager2.with<E3>().triggerEvent(E3{1, 2, 3});

	EventManagers<E, E1, E2, E3> manager3(manager2);

	manager3.with<E>().triggerEvent();
	manager3.with<E1>().triggerEvent(E1{1});
	manager3.with<E2>().triggerEvent(E2{1, 2});
	manager3.with<E3>().triggerEvent(E3{1, 2, 3});

	return 0;
}

#include <fstream>
#include <iostream>
#include <string>

#include "entity.h"
#include "component.h"
#include "type_id.h"
#include "system.h"

using namespace ECS;
using namespace std;

class A {};
class B : public A {};
class C {};

class Tranform : public Component {};
class Health : public Component {};

class Foo
{
public:

	~Foo()
	{
		std::cout << "dstructed\n";
	}
};

int main(int argc, char* argv[])
{
	cout << typeid(A).hash_code() << endl;
	cout << typeid(B).hash_code() << endl;
	cout << typeid(B).hash_code() << endl;
	cout << typeid(C).hash_code() << endl;

	cout << type<A>().id() 
		<< " " << type<B>().id()
		<< " " << type<B>().id() 
		<< endl;

	System<Foo> system;
	for (int i = 0; i < 4; ++i)
	{
		system.addComponent(i);
	}

	auto a = system.getComponent(1);
	system.removeComponent(1);

	return 0;
}
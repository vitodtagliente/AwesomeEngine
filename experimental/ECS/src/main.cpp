#include <fstream>
#include <iostream>
#include <string>

#include "ecs.h"

using namespace ECS;
using namespace std;

class A {};
class B : public A {};
class C {};

class Tranform : public DataComponent {};
class Health : public DataComponent {};

class Foo : public DataComponent
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

	return 0;
}
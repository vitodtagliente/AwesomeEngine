#include <fstream>
#include <iostream>
#include <string>

#include "entity.h"
#include "component.h"
#include "type_id.h"

using namespace ECS;
using namespace std;

class A {};
class B : public A {};
class C {};

class Tranform : public Component<Tranform> {};
class Health : public Component<Health> {};

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
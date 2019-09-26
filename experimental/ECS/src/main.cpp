#include <fstream>
#include <iostream>
#include <string>

#include "ecs.h"

using namespace ECS;
using namespace std;

class A {};
class B : public A {};
class C {};

template <typename T>
struct reflect
{
	using type = T;
};

struct transform
{
	int x, y, z;
};

class TransformSystem : public System<transform>
{
protected:

	virtual void each(const transform& t_data) override
	{
		cout << t_data.x << " " 
			<< t_data.y << " " 
			<< t_data.z << endl;
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

	Engine engine;

	TransformSystem system;
	system.addComponent(1);
	system.addComponent(2, transform{ 1, 2, 3 });
	system.update(0.1f);

	return 0;
}
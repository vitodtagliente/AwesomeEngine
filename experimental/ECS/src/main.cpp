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

	cout << type_id<A>()
		<< " " << type_id<B>()
		<< endl;

	Engine engine;
	Entity actor1 = engine.createEntity();
	
	engine.addSystem<TransformSystem>();

	// fake game loop
	for (auto i = 0; i < 10; ++i)
		engine.update(0.01f);

	return 0;
}
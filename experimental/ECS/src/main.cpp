#include <fstream>
#include <iostream>
#include <string>

#include "entity.h"
#include "component.h"
#include "type_id.h"

using namespace ECS;
using namespace std;

int main(int argc, char* argv[])
{
	TypeId id1, id2;
	cout << id1.get() << " " << id2.get() << endl;

	return 0;
}
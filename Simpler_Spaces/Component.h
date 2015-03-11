#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
using namespace std;

/* Components are Plain Old Data. Logic is separated into Subspace. */
class Component
{
public:

	bool valid;

	Component() : valid(true) {}
	Component(bool _valid) : valid(_valid) {}

	~Component() { cout << "Default Component Destructor. Bad?" << endl; }

};

#endif
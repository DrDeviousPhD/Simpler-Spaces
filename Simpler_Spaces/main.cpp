#include <iostream>
using namespace std;

#include "Space.h"

class Comp1 : public Component
{
public:
	Comp1() { cout << "Comp1 Constructed" << endl; }
	~Comp1() { cout << "Comp1 Destructed" << endl; }
};

class Comp2 : public Component
{
public:
	Comp2() { cout << "Comp2 Constructed" << endl; }
	~Comp2() { cout << "Comp2 Destructed" << endl; }
};

class Comp3 : public Component
{
public:
	Comp3() { cout << "Comp3 Constructed" << endl; }
	~Comp3() { cout << "Comp3 Destructed" << endl; }
};

class NotComp
{
public:
};

class Sub : public Subspace
{
public:
	Sub(Space* parent) : Subspace(parent)
	{

		addCompType<Comp1>();
		addCompType<Comp2>();

		// Should give us a message
		addCompType<Comp1>();
	}
};

int main()
{
	Space spc;
	Sub sub(&spc);

	/* Testing if addComp works */

	sub.addComp<Comp1>(0);
	sub.addComp<Comp2>(0);

	sub.addComp<Comp1>(0);	// Shouldn't work
	sub.addComp<Comp3>(0);	// Also shouldn't work

	/* Now testing if hasComp works */

	if (sub.hasComp<Comp1>(0)) { cout << "sub has Comp1 at 0" << endl; }
	if (sub.hasComp<Comp2>(0)) { cout << "sub has Comp2 at 0" << endl; }
	if (sub.hasComp<Comp3>(0)) { cout << "sub has Comp3 at 0" << endl; } // shouldn't show	(except that sub doesn't handle Comp3)

	if (sub.hasComp<Comp1>(1)) { cout << "sub has Comp1 at 1" << endl; }	// shouldn't show
	if (sub.hasComp<Comp2>(1)) { cout << "sub has Comp2 at 1" << endl; }	// shouldn't show
	if (sub.hasComp<Comp3>(1)) { cout << "sub has Comp3 at 1" << endl; }	// shouldn't show (except that sub doesn't handle Comp3)

	/* Now testing if we can remove components */

	/* Delete via object id (remove all components attached to objid) */

	sub.deleteObject(0);

	cin.get();

	return 0;
}
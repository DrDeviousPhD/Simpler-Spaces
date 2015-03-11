#include <iostream>
using namespace std;

#include "Space.h"

class Comp1 : public Component
{
public:
	Comp1() { cout << "Comp1 Constructed" << endl; }
	~Comp1() { cout << "Comp1 Destructed" << endl; }

	int a;
};

class Comp2 : public Component
{
public:
	Comp2() { cout << "Comp2 Constructed" << endl; }
	~Comp2() { cout << "Comp2 Destructed" << endl; }

	char b;
};

class Comp3 : public Component
{
public:
	Comp3() { cout << "Comp3 Constructed" << endl; }
	~Comp3() { cout << "Comp3 Destructed" << endl; }

	bool c;
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

	cout << "\nAdding components." << endl;

	sub.addComp<Comp1>(0);
	sub.addComp<Comp2>(0);

	sub.addComp<Comp1>(0);	// Shouldn't work
	sub.addComp<Comp3>(0);	// Also shouldn't work

	/* Now testing if hasComp works */

	cout << "\nTesting hasComp" << endl;

	if (sub.hasComp<Comp1>(0)) { cout << "sub has Comp1 at 0" << endl; }
	if (sub.hasComp<Comp2>(0)) { cout << "sub has Comp2 at 0" << endl; }
	if (sub.hasComp<Comp3>(0)) { cout << "sub has Comp3 at 0" << endl; } // shouldn't show	(except that sub doesn't handle Comp3)

	if (sub.hasComp<Comp1>(1)) { cout << "sub has Comp1 at 1" << endl; }	// shouldn't show
	if (sub.hasComp<Comp2>(1)) { cout << "sub has Comp2 at 1" << endl; }	// shouldn't show
	if (sub.hasComp<Comp3>(1)) { cout << "sub has Comp3 at 1" << endl; }	// shouldn't show (except that sub doesn't handle Comp3)


	/* Now try to get the components from the map */

	cout << "Testing getComp now." << endl;

	//auto comp = sub.getComp<Comp1>(0);

	/* Now testing if we can remove components */

	//cout << "\nTesting removeComp" << endl;

	//sub.removeComp<Comp1>(0);

	/* Delete via object id (remove all components attached to objid) */

	cout << "Attempting to delete all components attached to objid 0" << endl;

	sub.deleteObject(0);

	cout << "Do they still exist?" << endl;
	
	if (sub.hasComp<Comp1>(0) || sub.hasComp<Comp2>(0)) cout << "Yes." << endl;
	else if (sub.hasComp<Comp1>(0) == false && sub.hasComp<Comp2>(0) == false) cout << "Nope." << endl;

	///* Testing to see how we should delete objects in map */
	//
	//cout << "Plain ol object" << endl;
	//unordered_map<unsigned int, Comp1> test1;
	//test1.insert({ 0, Comp1() });
	//test1.erase(0);

	//cout << "Unique ptr" << endl;
	//unordered_map<unsigned int, unique_ptr<Comp1>> test2;
	//test2.insert({ 0, unique_ptr<Comp1>(new Comp1()) });
	//test2.erase(0);
	
	cin.get();

	return 0;
}
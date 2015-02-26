#ifndef SUBSPACE_H
#define SUBPSACE_H


/*

	TODO:	

		Adding components or component types should probably check and see if the type passed is derived from Component. Otherwise, if you pass a type that 
		isn't associated with Component at all you get a really ambiguous compile error: 
		
		"error C2679: binary '=' : no operator found which takes a right-hand operand of type 'std::unique_ptr<CompType,std::default_delete<_Ty>>' (or there is no acceptable conversion)"


		MAKE REMOVECOMP REMOVE THE OBJECTID FROM THE MAP

*/


#include <iostream>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
using namespace std;

#include "Component.h"

class Space;

class Subspace
{
private:

	Space* parent;

	/* < Component's type, U_map < object id, Component > >*/
	unordered_map < type_index, unordered_map < unsigned int, unique_ptr<Component> > > components;

protected:

	template < typename CompType >
	void addCompType()
	{
		/* 
			unordered_map's count() can be used to see if a key is already being used, since unordered maps can only be used once. 
			If count() returns 0, then components doesn't have that component type and we can add it.
		*/

		if (components.count(type_index(typeid(CompType))) == 0)
		{
			cout << "Size before: " << components.size() << endl;
			components.insert(make_pair(type_index(typeid(CompType)), unordered_map< unsigned int, unique_ptr<Component> >()));	// add CompType to components.
			cout << "Size after: " << components.size() << endl;
			cout << typeid(CompType).name() << "'s hash: " << typeid(CompType).hash_code() << endl;
		}
		else
		{
			cout << "Already handle type: " << typeid(CompType).name() << endl;
		}
		return;
	}

public:

	template < typename CompType >
	bool hasComp(unsigned int _objid)
	{
		/* Get type info */
		type_index type = typeid(CompType);

		/* First check if we handle this type of component */
		if (components.count(type) > 0)			// count() returns 1 if we do handle components of CompType
		{
			if (components[type].count(_objid) > 0)	// returns 1 if there is a component at _objid. That's bad in this case, and we should leave.
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			cout << "Unhandled type: " << type.name() << endl;
			return false;
		}
	}

	template < typename CompType >
	void addComp(unsigned int _objid)
	{
		/* This is probably a bad idea but I'd rather copy/paste code from hasComp than have to call find() twice. */

		/* Get type info */
		type_index type = typeid(CompType);

		/* First check if we handle this type of component */
		if (components.count(type) > 0)			// count() returns 1 if we do handle components of CompType
		{
			if (components[type].count(_objid) > 0)	// returns 1 if there is a component at _objid. That's bad in this case, and we should leave.
			{
				cout << "Already have a component " << type.name() << " at id " << _objid << endl;
				return;
			}

			/* Add the component */
			//components[type][_objid] = unique_ptr<CompType>(new CompType());
			components[type].insert({ _objid, unique_ptr<CompType>(new CompType()) });	// How bout this?


			return;
		}
		else
		{
			cout << "Unhandled type: " << type.name() << endl;
			return;
		}

		return;

	}

	template < typename CompType >
	void removeComp(unsigned int _objid)
	{
		/* Another copy/paste job */

		/* Get type info */
		type_index type = typeid(CompType);

		/* First check if we handle this type of component */
		if (components.count(type) > 0)			// count() returns 1 if we do handle components of CompType
		{
			
			if (components[type].count(_objid) > 0)	// returns 1 if there is a component at _objid. That's good in this case. We should delete it.
			{
				components[type][_objid].reset(nullptr);	// setting to nullptr deletes
				// REMOVE FROM MAP
				components[type].erase(_objid);
				return;
			}
			else
			{
				cout << "No object " << type.name() << " at id " << _objid << endl;
				return;
			}

		}
		else
		{
			
			cout << "Unhandled type: " << type.name() << endl;
			return;

		}

		return;
	}

	void deleteObject(unsigned int _objid)
	{
		/* Run through every type of component, check if object is in its associated map, erase() if it is.*/

		for (auto it = components.begin(); it != components.end(); it++)
		{
			if (it->second.count(_objid) > 0)	// If there is an object attached to that component
			{
				it->second.at(_objid).reset(nullptr);
				it->second.erase(_objid);	// Does this delete?
			}
		}
		return;
	}

	Subspace(Space* _parent) : parent(_parent) {}

};


#endif
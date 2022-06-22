#include <iostream>
#include "room.h"
#include "exit.h"

Exit::Exit(const string& name, const string& opposite_name, const string& description, Room* origin, Room* destination, bool one_way) :
	Entity(name, description, (Entity*)origin),
	closed(false), locked(false), key(NULL), one_way(one_way), destination(destination), opposite_name(opposite_name) {
	type = EXIT;

	if (one_way == false) destination->container.push_back(this);
}

Exit::~Exit() {}

void Exit::Look() const {
	//cout << endl << name << " to " << opposite_name;
	cout << endl << description << endl;
}

const string& Exit::GetNameFrom(const Room* room) const {
	if (room == parent) return name;
	if (room == destination) return opposite_name;

	return name; // error ?
}

Room* Exit::GetDestinationFrom(const Room* room) const {
	if (room == parent) return destination;
	if (room == destination) return (Room*)parent;

	return NULL;
}
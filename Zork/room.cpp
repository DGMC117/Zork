#include <iostream>
#include "globals.h"
#include "room.h"

Room::Room(const string& title, const string& description) :
	Entity(title, description, NULL) {
	type = ROOM;
}

Room::~Room() {}

void Room::Look() const {
	cout << endl << GREEN_ << name << _OFF << endl;
	cout << description;

	cout << endl;
}
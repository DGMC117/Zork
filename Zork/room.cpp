#include <iostream>
#include "globals.h"
#include "exit.h"
#include "item.h"
#include "creature.h"
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

Exit* Room::GetExit(const string& direction) const {
	for (auto it : container) {
		if (it->type == EXIT) {
			Exit* ex = (Exit*) it;
			if (Same(ex->GetNameFrom(this), direction)) return ex;
		}
	}
	return NULL;
}
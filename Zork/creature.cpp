#include <iostream>
#include "globals.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "creature.h"

Creature::Creature(const string& title, const string& description, Room* room) :
	Entity(title, description, (Entity*)room) {
	type = CREATURE;
	hit_points = 1;
}

Creature::~Creature() {}

Room* Creature::GetRoom() const {
	return (Room*)parent;
}

bool Creature::PlayerInRoom() const {
	return parent->Find(PLAYER) != NULL;
}

bool Creature::IsAlive() const {
	return hit_points > 0;
}

bool Creature::Go(const vector<string>& args) {
	if (!IsAlive()) return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL) return false;

	if (PlayerInRoom()) cout << name << "goes " << args[1] << "..." << endl;

	ChangeParentTo(exit->GetDestinationFrom((Room*)parent));

	return true;
}

void Creature::Look(const vector<string>& args) const {
	if (IsAlive()) {
		cout << name << endl;
		cout << description << endl;
	}
	else {
		cout << name << "'s corpse" << endl;
		cout << "Here lies dead: " << description << endl;
	}
}

bool Creature::Take(const vector<string>& args) {
	if (!IsAlive()) return false;

	Item* item = (Item*)parent->Find(args[1], ITEM);

	if (args.size() > 1) { // we could pick something from a container
		if (item == NULL) item = (Item*)Find(args[1], ITEM);

		if (item == NULL) return false;

		Item* subitem = (Item*)item->Find(args[3], ITEM);

		if (subitem == NULL) return false;

		if (PlayerInRoom()) cout << name << " looks into " << item->name << endl;

		item = subitem;
	}

	if (item == NULL) return false;

	if (PlayerInRoom()) cout << name << " takes " << item->name << "." << endl;

	item->ChangeParentTo(this);

	return true;
}

void Creature::Inventory() const {
	vector<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0) {
		cout << name << " does not own any items" << endl;
		return;
	}

	cout << endl << name << " owns:" << endl;
	for (auto it : items) {
		cout << it->name << endl;
	}
}

bool Creature::Drop(const vector<string>& args) {
	if (!IsAlive()) return false;

	Item* item = (Item*)Find(args[1], ITEM);

	if (item == NULL) return false;

	if (PlayerInRoom()) cout << name << " drops " << item->name << "..." << endl;

	item->ChangeParentTo(parent);

	return true;
}

void Creature::Tick() {}
#include <iostream>
#include "room.h"
#include "exit.h"
#include "globals.h"
#include "item.h"

Item::Item(const string& title, const string& description, Entity* parent, ItemType item_type) :
	Entity(title, description, parent), item_type(item_type) {
	type = ITEM;
	min_value = max_value = 0;
}

Item::~Item() {}

void Item::Look() const {
	cout << endl << name << endl;
	cout << description << endl;

	vector<Entity*> stuff;
	FindAll(ITEM, stuff);

	if (stuff.size() > 0) {
		cout << "It contains: " << endl;
		for (auto it : stuff) cout << it->name << endl;
	}
}

int Item::GetValue() const {
	return Roll(min_value, max_value);
}
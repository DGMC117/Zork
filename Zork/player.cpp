#include <iostream>
#include "globals.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "player.h"

Player::Player(const string& title, const string& description, Room* room) : 
	Creature(title, description, room) {
	type = PLAYER;
}

Player::~Player() {}

void Player::Look(const vector<string>& args) const {
	if (args.size() > 1) {
		for (auto it : parent->container) {
			if ((Same(it->name, args[1]) && it->type != EXIT) || (it->type == EXIT && Same(args[1], ((Exit*)it)->GetNameFrom((Room*)parent)))) {
				it->Look();
				return;
			}
		}

		if (Same(args[1], "me")) {
			cout << endl << YELLOW_ "" << name << "" _OFF << endl;
			cout << description << endl;
		}
	}
	else {
		parent->Look();
	}
}

bool Player::Go(const vector<string>& args) {
	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL) {
		cout << endl << "There is no exit at '" << args[1] << "'." << endl;
		return false;
	}

	if (exit->locked) {
		cout << endl << "That exit is locked." << endl;
		return false;
	}

	cout << endl << "You take direction " << exit->GetNameFrom((Room*)parent) << "..." << endl;
	ChangeParentTo(exit->GetDestinationFrom((Room*)parent));
	parent->Look();

	return true;
}

bool Player::Take(const vector<string>& args) {
	if (args.size() == 4) {
		Item* item = (Item*)parent->Find(args[3], ITEM);

		// we could pick something from a container
		if (item == NULL) item = (Item*)Find(args[3], ITEM);

		if (item == NULL) {
			cout << endl << "Cannot find '" << args[3] << "' in this room or in your inventory." << endl;
			return false;
		}

		Item* subitem = (Item*)item->Find(args[1], ITEM);

		if (subitem == NULL) {
			cout << endl << item->name << " does not contain '" << args[1] << "'." << endl;
			return false;
		}

		cout << endl << "You take " << subitem->name << " from " << item->name << "." << endl;
		subitem->ChangeParentTo(this);
	}
	else if (args.size() == 2) {
		Item* item = (Item*)parent->Find(args[1], ITEM);

		if (item == NULL) {
			cout << endl << "There is no item here with that name." << endl;
			return false;
		}

		cout << endl << "You take " << item->name << "." << endl;
		item->ChangeParentTo(this);
	}

	return false;
}

void Player::Inventory() const {
	vector<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0) {
		cout << endl << "You do not own any item." << endl;
		return;
	}

	for (auto it : items) {
		cout << endl << it->name;
	}

	cout << endl;
}

bool Player::Drop(const vector<string>& args) {
	if (args.size() == 2) {
		Item* item = (Item*)Find(args[1], ITEM);

		if (item == NULL) {
			cout << endl << "There is no item on you with that name." << endl;
			return false;
		}

		cout << endl << "You drop " << item->name << "..." << endl;
		item->ChangeParentTo(parent);

		return true;
	}
	else if (args.size() == 4) {
		Item* item = (Item*)Find(args[1], ITEM);

		if (item == NULL) {
			cout << endl << "Can not find '" << args[1] << "' in your inventory." << endl;
			return false;
		}

		Item* container = (Item*)parent->Find(args[3], ITEM);

		if (container == NULL) {
			container = (Item*)Find(args[3], ITEM);
			cout << endl << "Can not find '" << args[3] << "' in your inventory or in the room." << endl;
			return false;
		}

		cout << endl << "You put " << item->name << " into " << container->name << "." << endl;
		item->ChangeParentTo(container);

		return true;
	}

	return false;
}
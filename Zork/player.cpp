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

		if (subitem->locked) {
			cout << endl << item->lock_description << endl;
			return false;
		}

		if (!subitem->pickable) {
			cout << endl << "You can't pick " << subitem->name << " up." << endl;
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

		if (item->locked) {
			cout << endl << item->lock_description << endl;
			return false;
		}

		if (!item->pickable) {
			cout << endl << "You can't pick up " << item->name << endl;
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

bool Player::UnLock(const vector<string>& args) {
	if (!IsAlive()) return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL) {
		cout << endl << "There is no exit at '" << args[1] << "'." << endl;
		return false;
	}

	if (exit->locked == false) {
		cout << endl << "That exit is not locked." << endl;
		return false;
	}

	Item* item = (Item*)Find(args[3], ITEM);

	if (Same(args[3], "code")) {
		cout << endl << "Type the code for the door:" << endl;
		string code = "";
		cin >> code;
		if (!Same(code, exit->code)) {
			cout << endl << "Wrong code!" << endl;
			return false;
		}
	}
	else {
		if (item == NULL) {
			cout << endl << "Key '" << args[3] << "' not found in your inventory." << endl;
			return false;
		}

		if (exit->key != item) {
			cout << endl << "Key '" << item->name << "' is not the key for " << exit->GetNameFrom((Room*)parent) << "." << endl;
			return false;
		}
	}

	cout << endl << "You unlock " << exit->GetNameFrom((Room*)parent) << "..." << endl;

	exit->locked = false;

	return true;
}

bool Player::Break(const vector<string>& args) {
	if (!IsAlive()) return false;

	Item* item = (Item*)parent->Find(args[1], ITEM);
	Item* weapon = (Item*)Find(args[3], ITEM);

	// we could break something from a container
	if (item == NULL) item = (Item*)Find(args[1], ITEM);
	if (item == NULL) {
		cout << endl << "Object '" << args[1] << "' not found." << endl;
		return false;
	}
	
	if (weapon == NULL) {
		cout << endl << "Object '" << args[3] << "' not found not found in your inventory." << endl;
		return false;
	}

	if (item->broken) {
		cout << endl << "This is already broken!" << endl;
		return false;
	}

	if (weapon->item_type != WEAPON) {
		cout << endl << "I don't think you can break anything at all with this " << weapon->name << "." << endl;
		return false;
	}

	if (item->item_type != BREAKABLE) {
		cout << endl << "Doesn't seem like this is going to break soon..." << endl;
		return false;
	}

	item->Break();
	cout << endl << "You break " << item->name << " with " << weapon->name << "...";
	return true;
}

bool Player::Combine(const vector<string>& args) {
	if (!IsAlive()) return false;

	Item* comp1 = (Item*)Find(args[1], ITEM);
	Item* comp2 = (Item*)Find(args[3], ITEM);
	Item* tool	= (Item*)parent->Find(args[5], ITEM);
	if (tool == NULL) tool = (Item*)Find(args[5], ITEM);

	if (comp1 == NULL) {
		cout << endl << "Object '" << args[1] << "' not found in your inventory." << endl;
		return false;
	}

	if (comp2 == NULL) {
		cout << endl << "Object '" << args[3] << "' not found in your inventory." << endl;
		return false;
	}

	if (tool == NULL) {
		cout << endl << "Object '" << args[5] << "' not found." << endl;
		return false;
	}

	if (tool->item_type != COMBINER) {
		cout << endl << "You can't use " << args[5] << " to combine anything." << endl;
		return false;
	}

	if (tool->component1 != comp1 && tool->component2 != comp1) {
		cout << endl << "You can't combine " << args[1] << " using " << args[5] << endl;
		return false;
	}

	if (tool->component1 != comp2 && tool->component2 != comp2) {
		cout << endl << "You can't combine " << args[3] << " using " << args[5] << endl;
		return false;
	}

	cout << endl << "You combine " << args[1] << " and " << args[3] << " using " << args[5] << "..." << endl;
	comp1->ChangeParentTo(tool->combination_result->parent);
	comp2->ChangeParentTo(tool->combination_result->parent);
	tool->combination_result->ChangeParentTo(tool);
	return true;
}

bool Player::Transform(const vector<string>& args) {
	if (!IsAlive()) return false;

	Item* item = (Item*)Find(args[1], ITEM);
	Item* tool = (Item*)parent->Find(args[3], ITEM);
	if (tool == NULL) tool = (Item*)Find(args[3], ITEM);

	if (item == NULL) {
		cout << endl << "Object '" << args[1] << "' not found in your inventory." << endl;
		return false;
	}

	if (tool == NULL) {
		cout << endl << "Object '" << args[3] << "' not found." << endl;
		return false;
	}

	if (tool->item_type != TRANSFORMER) {
		cout << endl << "You can't use " << args[3] << " to transform anything." << endl;
		return false;
	}

	if (tool->transformable != item) {
		cout << endl << "You can't transform " << args[1] << " using " << args[3] << endl;
		return false;
	}

	cout << endl << "You transform " << args[1] << " using " << args[3] << "..." << endl;
	item->ChangeParentTo(tool->transform_result->parent);
	tool->transform_result->ChangeParentTo(tool);
	return true;
}

bool Player::Talk(const vector<string>& args) {
	if (!IsAlive()) return false;

	Creature* creature = (Creature*)parent->Find(args[1], CREATURE);

	if (creature == NULL) {
		cout << endl << "Creature '" << args[1] << "' not found." << endl;
		return false;
	}

	creature->Talk();
	return true;
}
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
		cout << endl << name << endl;
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

bool Creature::UnLock(const vector<string>& args) {
	if (!IsAlive()) return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL || exit->locked == false) return false;

	Item* item = (Item*)Find(args[3], ITEM);

	if (item == NULL || exit->key != item) return false;

	if (PlayerInRoom()) cout << endl << name << "unlocks " << exit->GetNameFrom((Room*)parent) << "..." << endl;

	exit->locked = false;

	return true;
}

void Creature::Talk() {
	if (dialog == "") {
		cout << endl << "..." << endl;
	}
	else {
		cout << endl << dialog << endl;
	}
}

bool Creature::Equip(const vector<string>& args) {
	if (!IsAlive()) return false;

	Item* item = (Item*)Find(args[1], ITEM);

	if (item == NULL) return false;

	switch (item->type) {
	case WEAPON:
		weapon = item;
		break;

	case ARMOUR:
		armour = item;
		break;

	default:
		return false;
	}

	if (PlayerInRoom()) cout << name << " equips " << item->name << "..." << endl;

	return true;
}

bool Creature::UnEquip(const vector<string>& args) {
	if (!IsAlive()) return false;

	Item* item = (Item*)Find(args[1], ITEM);

	if (item == NULL) return false;

	if (item == weapon) weapon = NULL;
	else if (item == weapon) armour = NULL;
	else return false;

	if (PlayerInRoom()) cout << name << " un-equips " << item->name << "..." << endl;

	return true;
}

bool Creature::AutoEquip() {
	if (!IsAlive()) return false;

	vector<Entity*> items;
	FindAll(ITEM, items);

	for (auto it : items) {
		Item* i = (Item*)it;

		if (i->item_type == WEAPON) weapon = i;
		if (i->item_type == ARMOUR) armour = i;
	}

	return true;
}

bool Creature::Attack(const vector<string>& args) {
	Creature* target = (Creature*)parent->Find(args[1], CREATURE);

	if (target == NULL) return false;

	combat_target = target;
	cout << endl << name << " attacks " << target->name << "!" << endl;
	return true;
}

int Creature::MakeAttack() {
	if (!IsAlive() || !combat_target->IsAlive()) {
		combat_target = combat_target->combat_target = NULL;
		return false;
	}

	int result = (weapon ? weapon->GetValue() : Roll(min_damage, max_damage)) + base_strength;

	if (PlayerInRoom()) cout << name << " attacks " << combat_target->name << " for " << result << endl;

	combat_target->ReceiveAttack(result);

	// make the attacker react and take me as a target
	if (combat_target->combat_target == NULL) combat_target->combat_target = this;

	return result;
}

int Creature::ReceiveAttack(int damage) {
	int prot = (armour) ? armour->GetValue() : Roll(min_protection, max_protection);
	int received = damage - prot;

	hit_points -= received;

	if (PlayerInRoom())
		cout << name << " is hit for " << received << " damage (" << prot << " blocked) " << endl;

	if (IsAlive() == false) Die();

	return received;
}

void Creature::Die()
{
	if (PlayerInRoom()) cout << name << " dies.";
}

bool Creature::Loot(const vector<string>& args)
{
	Creature* target = (Creature*)parent->Find(args[1], CREATURE);

	if (target == NULL && target->IsAlive() == false) return false;

	vector<Entity*> items;
	target->FindAll(ITEM, items);

	for (auto it : items) {
		Item* i = (Item*)it;
		i->ChangeParentTo(this);
	}

	cout << endl << name << " loots " << target->name << "'s corpse" << endl;

	return true;
}

void Creature::Stats() const {
	cout << endl << "Hit Points: " << hit_points;
	cout << endl << "Base Strength: " << base_strength;
	cout << endl << "Attack: (" << ((weapon) ? weapon->name : "no weapon") << ") ";
	cout << ((weapon) ? weapon->min_value : min_damage) << "-" << ((weapon) ? weapon->max_value : max_damage);
	cout << endl << "Protection: (" << ((armour) ? armour->name : "no armour") << ") ";
	cout << ((armour) ? armour->min_value : min_protection) << "-" << ((armour) ? armour->max_value : max_protection);
	cout << endl;
}

void Creature::Tick() {
	if (combat_target != NULL) {
		if (parent->Find(combat_target) == true)
			MakeAttack();
		else
			combat_target = NULL;
	}
}
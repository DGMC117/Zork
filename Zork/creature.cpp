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
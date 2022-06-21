#include <iostream>
#include "globals.h"
#include "entity.h"

Entity::Entity(const string& name, const string& description, Entity* parent = NULL) : 
	name(name), description(description), parent(parent) {
	type = ENTITY;

	if (parent != NULL) parent->container.push_back(this);
}

Entity::~Entity() {}

void Entity::Look() const {
	cout << name << endl;
	cout << description << endl;
}

void Entity::Tick() {}

void Entity::ChangeParentTo(Entity* new_parent) {
	if (parent != NULL) {
		vector<Entity*>::iterator it;
		it = remove(parent->container.begin(), parent->container.end(), this);
		(parent->container).erase(it);
	}

	parent = new_parent;

	if (parent != NULL) parent->container.push_back(this);
}

bool Entity::Find(Entity* entity) const {
	for (auto it : container) if (it == entity) return true;

	return false;
}

Entity* Entity::Find(EntityType type) const {
	for (auto it : container) if (it->type == type) return it;

	return NULL;
}

Entity* Entity::Find(const string& name, EntityType type) const {
	for (auto it : container) if (it->type == type) if (Same(it->name, name)) return it;

	return NULL;
}

void Entity::FindAll(EntityType type, vector<Entity*>& vector_to_fill) const {
	for (auto it : container) if (it->type == type) vector_to_fill.push_back(it);
}
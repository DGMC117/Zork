#ifndef __Entity__
#define __Entity__

#include <string>
#include <vector>

enum EntityType {
	ENTITY,
	ROOM,
	EXIT,
	ITEM,
	CREATURE,
	PLAYER
};

class Entity {
public:
	Entity(const string& name, const string& description, Entity* parent);
	virtual ~Entity();

	virtual void Look() const;
	virtual void Tick();

	void ChangeParentTo(Entity* new_parent);
	bool Find(Entity* entity) const;
	Entity* Find(EntityType type) const;
	Entity* Find(const string& name, EntityType type) const;
	void FindAll(EntityType type, vector<Entity*>& vector_to_fill) const;

public:
	EntityType type;
	string name;
	string description;

	Entity* parent;
	vector<Entity*> container;
};

#endif //__Entity__
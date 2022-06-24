#ifndef __Item__
#define __Item__

#include "entity.h"

class Room;

enum ItemType {
	COMMON,
	WEAPON,
	ARMOUR,
	BREAKABLE,
	COMBINER,
	TRANSFORMER
};

class Item : public Entity {
public:
	Item(const string& name, const string& description, Entity* parent, ItemType item_type = COMMON);
	~Item();
	
	void Look() const;
	int GetValue() const;
	void Break();

public:
	int min_value;
	int max_value;
	ItemType item_type;

	bool pickable = true; // Can it be picked up?

	bool locked = false; // Is it locked
	string lock_description; // Description of lock

	bool broken = false; // Is it broken
	Item* unlocks_when_broken;

	Item* component1; // First component of combination
	Item* component2; // Second component of combination
	Item* combination_result; // Result of combination

	Item* transformable; // Transformable item
	Item* transform_result; // Transformation result
};

#endif //__Item__
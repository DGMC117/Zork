#ifndef __Item__
#define __Item__

#include "entity.h"

class Room;

enum ItemType {
	COMMON,
	WEAPON,
	ARMOUR
};

class Item : public Entity {
public:
	Item(const string& name, const string& description, Entity* parent, ItemType item_type = COMMON);
	~Item();
	
	void Look() const;
	int GetValue() const;

public:
	int min_value;
	int max_value;
	ItemType item_type;
};

#endif //__Item__
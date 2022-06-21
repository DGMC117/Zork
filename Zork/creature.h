#ifndef __Creature__
#define __Creature__

#include <string>
#include "entity.h"

class Room;
class Item;

using namespace std;

class Creature : public Entity {
public:
	Creature(const string& name, const string& description, Room* room);
	~Creature();

	Room* GetRoom() const;
	bool PlayerInRoom() const;
	bool IsAlive() const;

public:
	int hit_points;
};

#endif //__Creature__
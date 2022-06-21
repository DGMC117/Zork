#ifndef __Exit__
#define __Exit__

#include "entity.h"

using namespace std;

class Room;

class Exit : public Entity {
public:
	Exit(const string& name, const string& opposite_name, const string& description, Room* origin, Room* destination, bool one_way = false);
	~Exit();

	void Look() const;

	const string& GetNameFrom(const Room* room) const;
	Room* GetDestinationFrom(const Room* room) const;

public:
	bool one_way;
	bool closed;
	bool locked;
	string opposite_name;
	Room* destination;

	Entity* key;
};

#endif //__Exit__
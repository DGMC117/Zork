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

	virtual bool Go(const vector<string>& args);
	virtual void Look(const vector<string>& args) const;
	virtual bool Take(const vector<string>& args);
	virtual bool Drop(const vector<string>& args);
	virtual void Inventory() const;
	virtual bool UnLock(const vector<string>& args);
	virtual void Tick();
	virtual void Talk();

public:
	int hit_points;

	string dialog = "";
};

#endif //__Creature__
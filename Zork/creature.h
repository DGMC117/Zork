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

	virtual bool Equip(const vector<string>& args);
	virtual bool UnEquip(const vector<string>& args);
	virtual bool AutoEquip();
	virtual bool Attack(const vector<string>& args);
	virtual int MakeAttack();
	virtual int ReceiveAttack(int damage);
	virtual void Die();
	virtual bool Loot(const vector<string>& args);
	virtual void Stats() const;

public:
	int hit_points;
	int min_damage;
	int max_damage;
	int min_protection;
	int max_protection;
	Creature* combat_target;
	Item* weapon;
	Item* armour;

	string dialog = "";
};

#endif //__Creature__
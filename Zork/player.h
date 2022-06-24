#ifndef __Player__
#define __Player__

#include "creature.h"

using namespace std;

class Player : public Creature {
public:
	Player(const string& name, const string& description, Room* room);
	~Player();

	bool Go(const vector<string>& args);
	void Look(const vector<string>& args) const;
	bool Take(const vector<string>& args);
	bool Drop(const vector<string>& args);
	bool UnLock(const vector<string>& args);
	void Inventory() const;
	bool Break(const vector<string>& args);
	bool Combine(const vector<string>& args);
	bool Transform(const vector<string>& args);
	bool Talk(const vector<string>& args);
	bool Use(const vector<string>& args);

	bool Examine(const vector<string>& args) const;
	bool Equip(const vector<string>& args);
	bool UnEquip(const vector<string>& args);
	bool Attack(const vector<string>& args);
	bool Loot(const vector<string>& args);

public:
	int max_hit_points = 20;

};

#endif //__Player__
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
	void Inventory() const;

public:

};

#endif //__Player__
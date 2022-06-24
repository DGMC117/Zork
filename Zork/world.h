#ifndef __World__
#define __World__

#include <string>
#include <vector>
#include <time.h>

#define TICK_FREQUENCY 0.5f

using namespace std;

class Entity;
class Player;

class World {
public:
	World();
	~World();

	bool Tick(vector<string>& args);
	bool ParseCommand(vector<string>& args);
	void GameLoop();
	bool IsPlayerAlive();

private:
	clock_t tick_timer;
	vector<Entity*> entities;
	Player* player;
};

#endif //__World__
#ifndef __World__
#define __World__

#include <string>
#include <vector>
#include <time.h>

#define TICK_FREQUENCY 0.5f

using namespace std;

class World {
public:
	World();
	~World();

	bool Tick(vector<string>& args);
	bool ParseCommand(vector<string>& args);
	void GameLoop();

private:
	clock_t tick_timer;
};

#endif //__World__
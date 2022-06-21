#include <iostream>
#include <fstream>
#include <sstream>

#include "globals.h"
#include "world.h"

World::World() {
	tick_timer = clock();
}

World::~World() {
}

bool World::Tick(vector<string>& args) {
	bool ret = true;

	if (args.size() > 0 && args[0].length() > 0) ret = ParseCommand(args);

	GameLoop();

	return ret;
}

void World::GameLoop() {
	clock_t now = clock();

	if ((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY) {
		tick_timer = now;
	}
}

bool World::ParseCommand(vector<string>& args) {
	bool ret = true;

	switch (args.size()) {
	default:
		ret = false;
	}

	return ret;
}
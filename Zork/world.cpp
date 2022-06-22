#include <iostream>
#include <fstream>
#include <sstream>

#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include "globals.h"
#include "entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"
#include "room.h"
#include "player.h"
#include "world.h"

World::World() {
	tick_timer = clock();

	// Rooms
	Room* recovery_room		= new Room("Recovery Room", "This is the recovery room.");
	Room* laboratory		= new Room("Laboratory", "This is the laboratory.");
	Room* exterior			= new Room("Exterior", "This is the exterior.");
	Room* hallway			= new Room("Hallway", "This is the hallway.");
	Room* assembly_room		= new Room("Assembly Room", "This is the assembly room.");
	Room* engineering_room	= new Room("Engineering Room", "This is the engineering room.");
	Room* reactor_room		= new Room("Reactor Room", "This is the reactor room.");

	entities.push_back(recovery_room);
	entities.push_back(laboratory);
	entities.push_back(exterior);
	entities.push_back(hallway);
	entities.push_back(assembly_room);
	entities.push_back(engineering_room);
	entities.push_back(reactor_room);

	// Exits
	Exit* recovery_to_laboratory	= new Exit("west", "east", "Door", laboratory, recovery_room);
	Exit* laboratory_to_exterior	= new Exit("south", "north", "Metal gate", exterior, laboratory);
	Exit* laboratory_to_hallway		= new Exit("west", "east", "Blue corridor", hallway, laboratory);
	Exit* hallway_to_assembly		= new Exit("south", "north", "Red corridor", assembly_room, hallway);
	Exit* hallway_to_engineering	= new Exit("west", "east", "Yellow corridor", engineering_room, hallway);
	Exit* engineering_to_reactor	= new Exit("north", "south", "Reinforced glass door", reactor_room, engineering_room);

	entities.push_back(recovery_to_laboratory);
	entities.push_back(laboratory_to_exterior);
	entities.push_back(laboratory_to_hallway);
	entities.push_back(hallway_to_assembly);
	entities.push_back(hallway_to_engineering);
	entities.push_back(engineering_to_reactor);

	// Player
	player = new Player("Cloud", "You are a soldier assigned to protect these installations with your life.", recovery_room);
	player->hit_points = 20;
	entities.push_back(player);
}

World::~World() {
	for (auto it : entities) delete it;
	entities.clear();
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
		for (auto it : entities) it->Tick();
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
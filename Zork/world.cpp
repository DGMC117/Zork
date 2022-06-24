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
	Exit* hallway_to_assembly		= new Exit("down", "up", "Stairs", assembly_room, hallway);
	Exit* hallway_to_engineering	= new Exit("west", "east", "Yellow corridor", engineering_room, hallway);
	Exit* engineering_to_reactor	= new Exit("north", "south", "Reinforced glass door", reactor_room, engineering_room);
	engineering_to_reactor->locked = true;
	engineering_to_reactor->exit_type = CODE;
	engineering_to_reactor->code = "2222";

	entities.push_back(recovery_to_laboratory);
	entities.push_back(laboratory_to_exterior);
	entities.push_back(laboratory_to_hallway);
	entities.push_back(hallway_to_assembly);
	entities.push_back(hallway_to_engineering);
	entities.push_back(engineering_to_reactor);

	// Items
	Item* glowdust	= new Item("Glowdust", "A strange yellow-ish dust that generates light.", recovery_room);
	Item* machine	= new Item("Machine", "A last generation recovery machine built to cure wounds.", recovery_room);
	Item* dagger	= new Item("Dagger", "A small but sharp dagger. It has a few holes in its blade to make it lighter.", recovery_room);
	Item* card		= new Item("Card", "A playing card for some strange game. The card's name seems to be 'Lightning Bolt'.", laboratory);
	Item* poster	= new Item("Poster", "A poster with a simple diagram depicting a flame, a water drop and... a lightbulb?.", laboratory);
	Item* burner	= new Item("Burner", "A standard-looking burner. The scientists here use them to make experiments.", laboratory);
	Item* box		= new Item("Box", "A cardboard box. It may have something inside of it.", hallway);
	Item* vibranium	= new Item("Vibranium", "A vibranium ingot. This is the strongest metal in the multi-verse! Wait, the what?", box);
	Item* frame		= new Item("Frame", "A cube-shaped metal frame. Looks like a component of some device.", assembly_room);
	Item* computer	= new Item("Computer", "A computer, used by the staff. You see there is an open email:\n\n    Hey Sisay,\n\n    Did you see that the number 2 looks like a duck?\n    I love ducks! Look, here are four ducks! 2222\n    From now on two is my favourite number, and I will use it for EVERYTHING!\n\n    Jhoira, from Engineering.\n\n...What a strange individual.", assembly_room);
	Item* forge		= new Item("Forge", "A huge forge that can shape any metal into any form. Maybe I could find a use for this?", assembly_room);
	Item* candybar	= new Item("Candybar", "A chocolate candybar. Looks yummy.", engineering_room);
	Item* biochip	= new Item("Biochip", "A powerful little device. But what is it for?", engineering_room);
	Item* battery	= new Item("Battery", "This battery looks as it contained an entire galaxy inside, despite being so small. There is a small printing on one side that says 'Orion'.", reactor_room);
	Item* bottle	= new Item("Bottle", "A glass bottle that contains a strange liquid. You feel as it was water, but it looks akward.", reactor_room);
	Item* cable		= new Item("Cable", "A very big cable, the size of an arm. it has yellow stripes.", reactor_room);

	entities.push_back(glowdust);
	entities.push_back(machine);
	entities.push_back(dagger);
	entities.push_back(card);
	entities.push_back(poster);
	entities.push_back(burner);
	entities.push_back(box);
	entities.push_back(vibranium);
	entities.push_back(frame);
	entities.push_back(computer);
	entities.push_back(forge);
	entities.push_back(candybar);
	entities.push_back(biochip);
	entities.push_back(battery);
	entities.push_back(bottle);
	entities.push_back(cable);

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
	case 1: // commands with no arguments
		if (Same(args[0], "look") || Same(args[0], "l")) {
			player->Look(args);
		}
		else if (Same(args[0], "north") || Same(args[0], "n")) {
			args.push_back("north");
			player->Go(args);
		}
		else if (Same(args[0], "south") || Same(args[0], "s")) {
			args.push_back("south");
			player->Go(args);
		}
		else if (Same(args[0], "east") || Same(args[0], "e")) {
			args.push_back("east");
			player->Go(args);
		}
		else if (Same(args[0], "west") || Same(args[0], "w")) {
			args.push_back("west");
			player->Go(args);
		}
		else if (Same(args[0], "up") || Same(args[0], "u")) {
			args.push_back("up");
			player->Go(args);
		}
		else if (Same(args[0], "down") || Same(args[0], "d")) {
			args.push_back("down");
			player->Go(args);
		}
		else if (Same(args[0], "inventory") || Same(args[0], "i")) {
			player->Inventory();
		}
		else ret = false;
		break;
	case 2: // commands with one arguments
		if (Same(args[0], "look") || Same(args[0], "l")) {
			player->Look(args);
		}
		else if (Same(args[0], "go")) {
			player->Go(args);
		}
		else if (Same(args[0], "take") || Same(args[0], "pick")) {
			player->Take(args);
		}
		else if (Same(args[0], "drop") || Same(args[0], "put")) {
			player->Drop(args);
		}
		else ret = false;
		break;
	case 4:
		if (Same(args[0], "take") || Same(args[0], "pick")) {
			player->Take(args);
		}
		else if (Same(args[0], "drop") || Same(args[0], "put")) {
			player->Drop(args);
		}
		else if (Same(args[0], "unlock") || Same(args[0], "unlk")) {
			player->UnLock(args);
		}
		else ret = false;
		break;
	default:
		ret = false;
	}

	return ret;
}
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

	Room* invisible_room	= new Room("Invisible Room", "You should not be here.");

	entities.push_back(recovery_room);
	entities.push_back(laboratory);
	entities.push_back(exterior);
	entities.push_back(hallway);
	entities.push_back(assembly_room);
	entities.push_back(engineering_room);
	entities.push_back(reactor_room);
	entities.push_back(invisible_room);

	// Exits
	Exit* recovery_to_laboratory	= new Exit("west", "east", "Door", laboratory, recovery_room);
	Exit* laboratory_to_exterior	= new Exit("south", "north", "A huge matal gate. Seems to require some kind of device to be able to open.", exterior, laboratory);
	laboratory_to_exterior->locked = true;
	laboratory_to_exterior->exit_type = KEY;
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

	// Creatures
	Creature* professor = new Creature("Professor", "Professor Ficus is a curious individual. He is a scholar in mythobeast studies.", laboratory);
	professor->hit_points = 5;
	professor->dialog = "Cloud!\nThis is bad, we have accidentally summoned one of the mythobeasts, Animar!\nWe need to capture it, or else it will destroy our installations.\nMaybe you could look for a metal frame and a biochip and build our latest prototype for capturing mythobeasts.\nPlease, help us! You are our only hope.\nAnimar is on the exterior of the installations, north from here.";
	Creature* spawn = new Creature("Spawn", "One of Animar's spawn, a minion.", hallway);
	spawn->hit_points = 10;
	Creature* animar = new Creature("Animar", "Animar, Soul of Elements.\nA powerful mythobeast that can shape the elements around it.\nYou feel an unknown pressure coming from its presence.", exterior);
	animar->hit_points = 99;
	animar->dialog = "Perish, mortal.";

	entities.push_back(professor);
	entities.push_back(spawn);
	entities.push_back(animar);

	// Items
	Item* glowdust	= new Item("Glowdust", "A strange yellow-ish dust that generates light.", recovery_room);
	Item* machine	= new Item("Machine", "A last generation recovery machine built to cure wounds.", recovery_room);
	machine->pickable = false;
	Item* dagger	= new Item("Dagger", "A small but sharp dagger. It has a few holes in its blade to make it lighter.", recovery_room, WEAPON);
	dagger->min_value = 2;
	dagger->max_value = 4;
	Item* card		= new Item("Card", "A playing card for some strange game. The card's name seems to be 'Lightning Bolt'.", laboratory);
	Item* poster	= new Item("Poster", "A poster with a simple diagram depicting a flame, a water drop and... a lightbulb?.", laboratory);
	Item* burner	= new Item("Burner", "A standard-looking burner. The scientists here use them to make experiments.", laboratory, COMBINER);
	burner->pickable = false;
	Item* box		= new Item("Box", "A cardboard box. It may have something inside of it.", hallway);
	Item* vibranium	= new Item("Vibranium", "A vibranium ingot. This is the strongest metal in the multi-verse! Wait, the what?", box);
	Item* frame		= new Item("Frame", "A cube-shaped metal frame. Looks like a component of some device.", assembly_room);
	frame->locked = true;
	frame->lock_description = "This frame is floating in a stream of pure plasma energy, it is too dangerous to pick up.\nThe machine that generates this stream has a beautiful design with yellow stripes going from one end of it to the other.";
	Item* computer	= new Item("Computer", "A computer, used by the staff. You see there is an open email:\n\n    Hey Sisay,\n\n    Did you see that the number 2 looks like a duck?\n    I love ducks! Look, here are four ducks! 2222\n    From now on two is my favourite number, and I will use it for EVERYTHING!\n\n    Jhoira, from Engineering.\n\n...What a strange individual.", assembly_room);
	computer->pickable = false;
	Item* forge		= new Item("Forge", "A huge forge that can shape any metal into any form. Maybe I could find a use for this?", assembly_room, TRANSFORMER);
	forge->pickable = false;
	Item* assembler = new Item("Assembler", "A machine that is able to combine two different components into one item.", assembly_room, COMBINER);
	assembler->pickable;
	Item* candybar	= new Item("Candybar", "A chocolate candybar. Looks yummy.", engineering_room);
	Item* biochip	= new Item("Biochip", "A powerful little device. But what is it for?", engineering_room);
	Item* battery	= new Item("Battery", "This battery looks as it contained an entire galaxy inside, despite being so small. There is a small printing on one side that says 'Orion'.", reactor_room);
	laboratory_to_exterior->key = battery;
	Item* bottle	= new Item("Bottle", "A glass bottle that contains a strange liquid. You feel as it was water, but it looks akward.", reactor_room);
	Item* cable		= new Item("Cable", "A very big cable, the size of an arm. it has yellow stripes.", reactor_room, BREAKABLE);
	cable->pickable = false;
	cable->unlocks_when_broken = frame;
	Item* potion = new Item("Potion", "A bright yellow liquid contained in a glass bottle. I wonder if I should use it...", invisible_room);
	burner->component1 = glowdust;
	burner->component2 = bottle;
	burner->combination_result = potion;
	Item* shield	= new Item("Shield", "A round, metal shield with a star in the middle. Looks like it can deflect any attack.", invisible_room, ARMOUR);
	shield->min_value = 5;
	shield->max_value = 10;
	forge->transformable = vibranium;
	forge->transform_result = shield;
	Item* mythocube	= new Item("Mythocube", "A cubic device designed to capture mythobeasts.", invisible_room);
	assembler->component1 = frame;
	assembler->component2 = biochip;
	assembler->combination_result = mythocube;
	Item* photo		= new Item("Photo", "A family picture. Depicts the professor and their beautiful wife and children.", professor);
	Item* claws		= new Item("Claws", "Sharp claws that can cut through metal.", spawn, WEAPON);
	claws->min_value = 2;
	claws->max_value = 3;
	spawn->AutoEquip();
	Item* staff = new Item("Staff", "A powerful staff that can summon the power of the elements.", animar, WEAPON);
	staff->min_value = 6;
	staff->max_value = 12;
	animar->AutoEquip();

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
	entities.push_back(potion);
	entities.push_back(shield);
	entities.push_back(assembler);
	entities.push_back(mythocube);
	entities.push_back(photo);
	entities.push_back(claws);
	entities.push_back(staff);

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
		else if (Same(args[0], "stats") || Same(args[0], "st")) {
			player->Stats();
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
		else if (Same(args[0], "talk")) {
			player->Talk(args);
		}
		else if (Same(args[0], "equip") || Same(args[0], "eq")) {
			player->Equip(args);
		}
		else if (Same(args[0], "unequip") || Same(args[0], "uneq")) {
			player->UnEquip(args);
		}
		else if (Same(args[0], "examine") || Same(args[0], "ex")) {
			player->Examine(args);
		}
		else if (Same(args[0], "attack") || Same(args[0], "at")) {
			player->Attack(args);
		}
		else if (Same(args[0], "loot") || Same(args[0], "lt")) {
			player->Loot(args);
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
		else if (Same(args[0], "break") || Same(args[0], "brk")) {
			player->Break(args);
		}
		else if (Same(args[0], "transform") || Same(args[0], "tra")) {
			player->Transform(args);
		}
		else ret = false;
		break;
	case 6:
		if (Same(args[0], "combine") || Same(args[0], "com")) {
			player->Combine(args);
		}
		else ret = false;
		break;
	default:
		ret = false;
	}

	return ret;
}

bool World::IsPlayerAlive() {
	return player->IsAlive();
}
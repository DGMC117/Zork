#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "globals.h"
#include "world.h"

using namespace std;

#define _OFF "\033[0m"
#define BLUE_ "\033[1;34m"
#define GREEN_ "\033[0;32m"
#define RED_ "\033[0;31m"
#define YELLOW_ "\033[0;33m"

int main() {

	char key;
	string player_input;
	vector<string> args;
	args.reserve(10);

	cout << BLUE_ "Welcome to Blue Mesa!" _OFF << endl;
	cout << "--------------------" << endl;

	World my_world;

	args.push_back("look");

	while (1) {
		if (_kbhit() != 0) {
			key = _getch();
			if (key == '\b') { // backspace
				if (player_input.length() > 0) {
					player_input.pop_back();
					cout << '\b';
					cout << " ";
					cout << '\b';
				}
			}
			else if (key != '\r') { // not return
				player_input += key;
				cout << key;
			}
			else Tokenize(player_input, args);
		}

		if (args.size() > 0 && Same(args[0], "quit")) break;

		if (my_world.Tick(args) == false) cout << endl << endl << "Sorry, I do not understand your command." << endl;

		if (args.size() > 0) {
			args.clear();
			player_input = "";
			cout << endl << "> ";
		}
	}

	cout << endl << endl << BLUE_ "Thank you for playing, Bye!" _OFF << endl;
	return 0;
}
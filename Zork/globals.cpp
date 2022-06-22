#include "globals.h"

bool Same(const string& a, const string& b) {
	return _stricmp(a.c_str(), b.c_str()) == 0;
}

void Tokenize(const string& line, vector<string>& args) {
	const char* str = line.c_str();

	do {
		const char* begin = str;

		while (*str != ' ' && *str) str++;

		args.push_back(string(begin, str));
	} while (0 != *str++);
}

int Roll(int min, int max) {
	return (max > 0) ? min + (rand() % (max - min)) : 0;
}

void split(const string& line, vector<string>& parameters, const string delimeter) {

	string aux = line;

	int pos = 0;
	string token;

	while ((pos = aux.find(delimeter)) != string::npos) {
		token = aux.substr(0, pos);
		aux.erase(0, pos + delimeter.length());
		parameters.push_back(token);
	}

	parameters.push_back(aux);

}
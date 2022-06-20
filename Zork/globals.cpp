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
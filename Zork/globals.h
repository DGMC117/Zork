#ifndef __Globals__
#define __Globals__

#include <string>
#include <vector>

using namespace std;

#define _OFF "\033[0m"
#define BLUE_ "\033[1;34m"
#define GREEN_ "\033[0;32m"
#define RED_ "\033[0;31m"
#define YELLOW_ "\033[0;33m"

bool Same(const string& a, const string& b);
void Tokenize(const string& line, vector<string>& args);
int Roll(int min, int max);
void split(const string& line, vector<string>& parameters, const string delimeter);

#endif //__Globals__
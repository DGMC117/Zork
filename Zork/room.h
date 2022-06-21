#ifndef __Room__
#define __Room__

#include "entity.h"

class Room : public Entity {
public:
	Room(const string& name, const string& description);
	~Room();

	void Look() const;

public:

};

#endif //__Room__
#include "AdvMotionTableEntry.h"

AdvMotionTableEntry::AdvMotionTableEntry(string dir, int room, string key)
{
	direction = dir;								// sets variables
	destinationRoom = room;
	keyName = key;
}

AdvMotionTableEntry::AdvMotionTableEntry(string dir, int room)
{
	direction = dir;			// sets variables 
	destinationRoom = room;
}

int AdvMotionTableEntry::getDestinationRoom()
{
	return destinationRoom;		//returns the room
}

string AdvMotionTableEntry::getDirection()
{
	return direction;		//returns the direction
}

string AdvMotionTableEntry::getKeyName()
{
	return keyName;			// returns the key name
}

#include "AdvRoom.h"



AdvRoom::AdvRoom()
{
	visited = false;
}

bool AdvRoom::readRoom(ifstream &roomFile)		// Reads room data from an open file. 
												// Returns true if successful.
{
	string strTemp;
	string descTemp;
	string direction;
	int room;

	roomFile.unget();
	if (!roomFile)
	{
		return false;
	}
	else
	{
		getline(roomFile, strTemp);		// reads in the room number
		rmNum = stoi(strTemp);

		getline(roomFile, strTemp);		// reads in the room name
		roomName = strTemp;

		while (strTemp != "-----")
		{
			getline(roomFile, strTemp);
			descTemp += strTemp;
			
		}
		
		description = descTemp;			// gets description

		while (getline(roomFile, strTemp) && !strTemp.empty())		// lastly gets the direction and the room
		{
			stringstream strSep(strTemp);
			strSep >> direction;
			strSep >> room;
			AdvMotionTableEntry temp(direction, room);
			motionTable.push_back(temp);
		}
	}
	return true;
}

string AdvRoom::getDescription()	// Return the room description.
{
		return description;
		
}

string AdvRoom::getName()	// Returns the room name.
{
	return roomName;
}
void AdvRoom::addObject(AdvObject obj)	// Adds an object to the room.
{
	// This function should add the obj to the room.
	// It however, should not add the object to the room
	// if the room already contains the object. 
	objects.push_back(obj);

}

void AdvRoom::removeObject(string objName)	// Removes an object with name objName and returns the object.
{
	// This function should remove the object with objName.
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].getName() == objName)
		{
			objects.erase(objects.begin() + i);
			break;
		}
	}
	return;
}

bool AdvRoom::containsObject(string objName)	  // Return true if the room contains an object with objName.
{
	// Returns true if object with objName is in the room.
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].getName() == objName)
			return true;
		else
			return false;
	}
}

int AdvRoom::objectCount()	// Returns how many objects are in the room.
{
	return objects.size();
}

AdvObject AdvRoom::getObject(int index)	// Returns object index from the room.
{
	return objects[index];
}

bool AdvRoom::hasBeenVisited()	// Returns true if the room has been visited. False otherwise.
{
	return visited;
}

void AdvRoom::setVisited(bool flag)	// Sets if the room has been visited.
{
	visited = flag;
}

vector<AdvMotionTableEntry> AdvRoom::getMotionTable()	// Returns a motion table for the room.
{
	return motionTable;
}


int AdvRoom::getRoomNumber()	// Returns the room number.
{
	return rmNum;
}

vector<AdvObject> AdvRoom::getObjects()		// gets all the objects and returns it from the vector
{
	return objects;
}

void AdvRoom::dropObject(AdvObject obj)
{
	objects.push_back(obj);		//pushes it back in the object vector
}
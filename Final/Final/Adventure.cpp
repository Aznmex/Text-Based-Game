#include "Adventure.h"

/*
* File: Adventure.cpp
* --------------------
* This program plays the Adventure game.
*/

Adventure::Adventure()
{

}

Adventure::Adventure(string objfile, string rmfile, string cmdfile)
{
	// Setup of the Adventure game using some files.
	LoadRooms(rmfile);		
	LoadObjects(objfile);
	LoadSynonyms(cmdfile);
	currRoomInd = 1;
}

void Adventure::Play()
{
	cout << rooms[currRoomInd - 1].getDescription() << endl;		// displays the user in the current room and sets that room to visited right after
	rooms[currRoomInd - 1].setVisited(true);

	while (currRoomInd != 0) {
		string cmd, objName;
		GetUserCmd(cmd, objName);
		if (cmd == "QUIT" || cmd == "Q") {
			QuitCmd();
			cout << "Goodbye!" << endl;
			return;
		}
		else if (cmd == "HELP") {
			HelpCmd();
		}
		else if (cmd == "LOOK" || cmd == "L")
		{
			cout << rooms[currRoomInd - 1].getDescription() << endl;
		}
		else if (cmd == "INVENTORY" || cmd == "I")
		{
			Inventory();
		}
		else if (cmd == "TAKE" || cmd == "CATCH")
		{
			Take();
		}
		else if (cmd == "DROP" || cmd == "RELEASE")
		{
			Drop();
		}
		else
		{
			MotionCmd(cmd);
		}
		// Runs through the commands that the user inputs and checks them
	}

	cout << "Goodbye!" << endl;
}


void Adventure::GetUserCmd(string &verb, string &obj)
{
	cout << "> ";
	string line;
	getline(cin, line);

	stringstream strSep(line);
	strSep >> verb;
	strSep >> obj;

	ConvertToUpper(verb);
	ConvertToUpper(obj);

	cmd = verb;
	objectName = obj;		// gets the user command and then seperates it if needed, then converts it to uppercase 
}

int Adventure::MotionCmd(string motion)
{
	// Get the motion table of the room number where the player is currently.
	// For each table entry, check to see if there is an entry that matches
	// "motion".  If the entry matches, check if the motion requires
	// a key and if the player has the has the key. A successful match
	// moves the player into the destination room.
	motions = rooms[currRoomInd - 1].getMotionTable();
	objects = rooms[currRoomInd - 1].getObjects();

	if (!inventory.empty())									// checks if the inventory is empty, and if it isn't then check the motions of the room 
	{
		for (int i = 0; i < inventory.size(); i++)
		{
			for (int m = 0; m < motions.size(); m++)
			{
				if (motions[m].getDirection() == "FORCED")			// if forced then force the user into that direction
				{
					currRoomInd = motions[m].getDestinationRoom();
				}
				if (inventory[i].getName() == motions[m].getKeyName())		// gets the key name and then checks the where it needs to be headed
				{
					currRoomInd = motions[m].getDestinationRoom();
					break;
				}
				else if (motion == motions[m].getDirection())			// gets destination
				{
					currRoomInd = motions[m].getDestinationRoom();
				}

			}
		}
	}
	else
	{
		for (int i = 0; i < motions.size(); i++)				// if the inventory is empty, but had a destination, then send the user there
		{
			if (motions[i].getDirection() == "FORCED")
			{
				currRoomInd = motions[i].getDestinationRoom();
			}
			else if (motion == motions[i].getDirection())
			{
				currRoomInd = motions[i].getDestinationRoom();
			}
		}

	}
	
	
	rooms[currRoomInd - 1].setVisited(true);
	
	if (rooms[currRoomInd - 1].hasBeenVisited()) {		// if the room has been visited display the room name 
		cout << rooms[currRoomInd - 1].getName() << endl;
	}
	else {
		cout << rooms[currRoomInd - 1].getDescription() << endl;	// else display the description
	}
	
	if (rooms[currRoomInd - 1].objectCount() != 0) {			// displays if there is an object in the current room
		for (int i = 0; i < rooms[currRoomInd - 1].objectCount(); i++) {
			AdvObject object;
			object = rooms[currRoomInd - 1].getObject(i);
			cout << "There is " << object.getDescription() << " here" << endl;
		}
	}

	return -1;
}

void Adventure::Take()
{
	objects = rooms[currRoomInd - 1].getObjects();	// sets objects to be the objects the that room
	if (!objects.empty())							// checks if the vetor is empty
	{
		for (int i = 0; objects.size() > i; i++)			//loops through the vector 
		{
			if (objects[i].getName() == objectName)				// gets the objects name and checks it with the user's command
			{
				AdvObject Object = objects[i];			// creats temp Adventure Object and sets it to the objects elements 
				inventory.push_back(Object);			// pushes it back into the inventory 
				cout << objects[i].getName() << " has been taken!" << endl; // displays the object that was taken
			}
			else
			{
				cout << "Item couldn't be found!" << endl;		// tells the user that there was no item if not found
			}
		}
	}
	else
	{
		cout << "There are no objects in this room!" << endl;
	}

}

void Adventure::Drop()
{
	if (!inventory.empty())		// checks if the inventory is not empty
	{
		for (int i = 0; i < inventory.size(); i++)
		{
			if (inventory[i].getName() == objectName)		// if the objects name matches the users command 
			{
				cout << "Dropped " << inventory[i].getName() << endl;
				AdvObject object = inventory[i];			// creates temp Adventure Object and sets that object to the inventory element in that vector
				rooms[currRoomInd - 1].dropObject(object);	// pushes the temp object into the room's object vector
				inventory.erase(inventory.begin() + i);		// removes the object from players inventory
				break;
			}
		}
	}
	else
	{
		cout << "Nothing to drop in inventory!" << endl;
	}
}

void Adventure::LoadObjects(string filename)
{
	// Should load all the objects from a file.
	ifstream objectFile;
	char dump;

	objectFile.open(filename);
	if (!objectFile)
	{
		cout << "Object file could not opened!" << endl;		// displays if the object file couldn't be opened
	}
	else
	{
		while (objectFile >> dump)
		{
			AdvObject object;
			if (!object.readObject(objectFile))
				break;
			else
			{
				rooms[object.getInitialLocation() - 1].addObject(object);		// add objects into the room vector
			}

		}
	}

}

void Adventure::LoadRooms(string filename)
{
	// Should load all rooms from a file
	ifstream roomFile;
	char dump;

	roomFile.open(filename);
	if (!roomFile)
	{
		cout << "Room file could not be opened!" << endl;		// displays if the room file couldn't be opened
	}
	else
	{
		while (roomFile >> dump)					
		{
			AdvRoom room;
			if (!room.readRoom(roomFile))				
				break;
			else
				rooms.push_back(room);			// pushes back the rooms into the room vector
		}
	}
}

void Adventure::LoadSynonyms(string filename)
{
	// Should load all synonyms from a file.
	ifstream synonymFile;
	string tempstring;

	synonymFile.open(filename);
	if (!synonymFile)
	{
		cout << "Synonym file could not be opened!" << endl;
	}
	else
		while (getline(synonymFile, tempstring) && !tempstring.empty())
		{
			Synonym syn;
			istringstream stringSeparation(tempstring);		// seperates the synonym and words
			stringSeparation >> syn.synonym;
			stringSeparation >> syn.word;
			synonyms.push_back(syn);					// pushes it into the vector
		}
}

/*
* Returns a synonym if one exists.  Otherwise returns original word.
*/
string Adventure::GetSynonym(string word)
{
	ConvertToUpper(word);		//converts the word and then returns it
	return word;
}


void Adventure::QuitCmd()
{
	// Ask if the uses would like to quit.  Should only take a yes or no.
	while (true) {
		string ans;
		cout << "Are you sure you want to quit now? ";
		getline(cin, ans);
		ConvertToUpper(ans);
		if (ans == "Y" || ans == "YES") {
			currRoomInd = 0;
			break;
		}
		if (ans == "N" || ans == "NO") {
			break;
		}
		cout << "Please answer yes or no." << endl;
	}
}

void Adventure::HelpCmd()
{
	cout << "Welcome to Adventure!" << endl;
	cout << "Somewhere nearby is Colossal Cave, where others have found fortunes in" << endl;
	cout << "treasure and gold, though it is rumored that some who enter are never" << endl;
	cout << "seen again. Magic is said to work in the cave.I will be your eyes" << endl;
	cout << "and hands. Direct me with natural English commands; I don't understand" << endl;
	cout << "all of the English language, but I do a pretty good job." << endl << endl;

	cout << "It's important to remember that cave passages turn a lot, and that" << endl;
	cout << "leaving a room to the north does not guarantee entering the next from" << endl;
	cout << "the south, although it often works out that way. You'd best make yourself" << endl;
	cout << "a map as you go along." << endl << endl;

	cout << "Much of my vocabulary describes places and is used to move you there." << endl;
	cout << "To move, try words like IN, OUT, EAST, WEST, NORTH, SOUTH, UP, or DOWN." << endl;
	cout << "I also know about a number of objects hidden within the cave which you" << endl;
	cout << "can TAKE or DROP.To see what objects you're carrying, say INVENTORY." << endl;
	cout << "To reprint the detailed description of where you are, say LOOK.If you" << endl;
	cout << "want to end your adventure, say QUIT." << endl;
}

void Adventure::Inventory()
{
	if (inventory.empty())
	{
		cout << "You have nothing in your inventory!" << endl;		// displays if there is nothing in the inventory
	}
	else
	{
		for (int i = 0; inventory.size() > i; i++)				// displays inventory
		{
			cout << inventory[i].getName() << endl;
		}
	}
}



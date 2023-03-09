#include "AdvObject.h"

AdvObject::AdvObject()
{

}

AdvObject::AdvObject(string objName, string objDes, int loc)
{
	objectName = objName;
	objectDescription = objDes;
	location = loc;
}

bool AdvObject::readObject(ifstream &objFile)
{
	string str;
	// True if able to read name, 
	// description, and initial location.
	// Otherwise returns false.
	objFile.unget();
	if (!objFile)
	{
		return false;
	}
	else {
		getline(objFile, str);
		objectName = str;
		getline(objFile, str);
		objectDescription = str;
		getline(objFile, str);
		location = stoi(str);
		return true;
	}

}

string AdvObject::getName()		// gets name and returns the objects name
{
	return objectName;
}

string AdvObject::getDescription()		// gets the description and returns the objects description
{
	return objectDescription;
}

int AdvObject::getInitialLocation()		// gets the initial location for the object and returns the location
{
	return location;
}
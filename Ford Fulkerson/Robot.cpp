#include "Robot.h"

Robot::Robot(int lor, int b)
{
	labelOfRobot = lor;
	battery = b;
	fullness = 0;
}

bool Robot::SetWhichjObjects(int index)
{
	if ((battery - fullness) != 0)
	{
		whichObjects.push_back(index);
		fullness++;
		return true;
	}
	else
		return false;
}

string Robot::Print()
{
	string tmp;

	if (whichObjects.size() == 0)
	{
		tmp = "None";
	}
	else
	{
		for (int i = 0; i < whichObjects.size(); i++)
			tmp += " " + IntToString(whichObjects[i] + 1);
	}

	return tmp;
}

string Robot::IntToString(int number)
{
	ostringstream oss;
	oss << number;
	return oss.str();
}
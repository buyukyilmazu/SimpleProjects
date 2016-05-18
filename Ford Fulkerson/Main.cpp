#include "Object.h"
#include "Robot.h"
#include<iostream>
#include<fstream>

void ReadFile(int &, int &, vector<Object> &, vector<Robot> &);
void NetworkFlowAlgorithm(int, vector<Object> &, vector<Robot> &);
void CreateOutput(int, vector<Robot> &);

int main()
{
	int numOfObjects, numOfRobots;
	vector<Object>Objects;
	vector<Robot>Robots;

	ReadFile(numOfObjects, numOfRobots, Objects, Robots);
	
	NetworkFlowAlgorithm(numOfObjects, Objects, Robots);

	CreateOutput(numOfRobots, Robots);

	return 0;
}

void ReadFile(int &numOfObjects, int &numOfRobots, vector<Object> &Objects, vector<Robot>&Robots)
{
	ifstream input("input.txt");

	string tmp;
	input >> numOfObjects >> numOfRobots;
	getline(input, tmp);

	for (int i = 0; i < numOfObjects; i++)
	{
		getline(input, tmp);
		Object newObject(i);
		Objects.push_back(newObject);
		int k = 0;

		for (int j = 0; j < tmp.size(); j = j + 2)
		{
			if (tmp[j] == '1')
			{
				Objects[i].whichRobotsPickUp.push_back(k);
				k++;
			}
			else
			{
				k++;
			}
		}
	}

	int tmp2;
	for (int i = 0; i < numOfRobots; i++)
	{
		input >> tmp2;
		Robot newRobots(i, tmp2);
		Robots.push_back(newRobots);
	}

	input.close();
}

void NetworkFlowAlgorithm(int numOfObjects, vector<Object> &Objects, vector<Robot> &Robots)
{
	int maxPickUp = Objects[0].whichRobotsPickUp.size();

	for (int i = 1; i < numOfObjects; i++)
	if (Objects[i].whichRobotsPickUp.size() > maxPickUp)
		maxPickUp = Objects[i].whichRobotsPickUp.size();

	int k = 1;

	while (k <= maxPickUp)
	{
		for (int i = 0; i < numOfObjects; i++)
		{
			for (int j = 0; j < Objects[i].whichRobotsPickUp.size(); j++)
			{
				if (!Objects[i].GetIsObjectSet() && Objects[i].whichRobotsPickUp.size() == k)
				{
					if (Robots[Objects[i].whichRobotsPickUp[j]].SetWhichjObjects(Objects[i].GetLabelOfObject()))
					{
						break;
					}
				}
			}
		}
		k++;
	}
}

void CreateOutput(int numOfRobots, vector<Robot> &Robots)
{
	for (int i = 0; i < numOfRobots; i++)
	{
		cout << i + 1 << ". Robots will be carry: " << Robots[i].Print() << endl;
	}
}
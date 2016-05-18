#include<vector>
#include<string>
#include<sstream>

using namespace std;

class Robot
{
private:
	int labelOfRobot;
	int battery;
	int fullness;
	vector<int> whichObjects;
public:
	Robot(int, int);
	bool SetWhichjObjects(int);
	string Print();
	string IntToString(int);
};


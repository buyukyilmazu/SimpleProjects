#include<vector>

using namespace std;

class Object
{
private:
	int labelOfObject;
	bool isObjectSet;
	
public:
	vector<int> whichRobotsPickUp;
	Object(int);
	bool GetIsObjectSet();
	int GetLabelOfObject();
};


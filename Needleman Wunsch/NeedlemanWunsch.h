#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include <stdlib.h> 

using namespace std;

class NeedlemanWunsch
{

private:
	
	int **scoreTable;
	string sequence1;
	string sequence2;
	int lengthOfSeq1;
	int lengthOfSeq2;
	int size;
	vector< vector<string> > mmgTable;
	vector<int> tracebackPosition;
	string output1;
	string output2;

public:

	NeedlemanWunsch();
	void ReadFile();
	void AllocateScoreTable();
	void CreateScoreTable();
	int Highest(int, int);
	bool HighestNeighbour(int, int);
	void CreateOutput();
	int IndexFound(char);
	~NeedlemanWunsch();
};
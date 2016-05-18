#include "NeedlemanWunsch.h"	

NeedlemanWunsch::NeedlemanWunsch()
{
	size = 0;
}

void NeedlemanWunsch::ReadFile()
{
	string tmp, info;

	sequence1 = "-";
	sequence2 = "-";

	ifstream input1("human-hemoglobin-sequence.fasta");

	getline(input1, info);
	while (getline(input1, tmp))
	{
		sequence1 = sequence1 + tmp;
	}

	input1.close();

	ifstream input2("mouse-hemoglobin-sequence.fasta");

	getline(input2, info);
	while (getline(input2, tmp))
	{
		sequence2 = sequence2 + tmp;
	}

	input2.close();

	lengthOfSeq1 = sequence1.size()-1;
	lengthOfSeq2 = sequence2.size()-1;

	ifstream input3("BLOSUM62.txt");

	getline(input3, tmp);

	while (tmp[0] == '#')
		getline(input3, tmp);

	for (int i = 0; i < tmp.size(); i++)
	{
		if (tmp[i] != ' ')
			size++;
	}

	for (int i = 0; i < size; i++) 
	{
		vector<string> row; 
		for (int j = 0; j < size+1; j++)
		{
			input3 >> tmp;
			row.push_back(tmp); 
		}
		mmgTable.push_back(row); 
	}

	input3.close();

	AllocateScoreTable();
}

void NeedlemanWunsch::AllocateScoreTable()
{

	scoreTable = new int*[lengthOfSeq2 + 1];
	
	for (int i = 0; i < lengthOfSeq2 + 1; i++)
	{
		scoreTable[i] = new int[lengthOfSeq1 + 1];
	}

	scoreTable[0][0] = 0;

	for (int i = 1; i < lengthOfSeq1+1; i++)
	{
		scoreTable[i][0] = scoreTable[i-1][0]+atoi(mmgTable[size-1][1].c_str());
	}

	for (int i = 1; i < lengthOfSeq2+1; i++)
	{
		scoreTable[0][i] = scoreTable[0][i - 1] + atoi(mmgTable[size-1][1].c_str());
	}
}

void NeedlemanWunsch::CreateScoreTable()
{

	for (int i=1; i < lengthOfSeq2 + 1; i++)
	{
		for (int j=1; j < lengthOfSeq1 + 1; j++)
		{
		scoreTable[i][j] = Highest(i, j);	
		}
	}

	tracebackPosition.push_back(lengthOfSeq2);
	tracebackPosition.push_back(lengthOfSeq1);

	HighestNeighbour(lengthOfSeq2, lengthOfSeq1);
}

int NeedlemanWunsch::Highest(int i, int j)
{
	int highest = scoreTable[i][j - 1] + atoi(mmgTable[size-1][1].c_str());
	int i1j1;


	if (highest < scoreTable[i - 1][j] + atoi(mmgTable[size - 1][1].c_str()))
		highest = scoreTable[i - 1][j] + atoi(mmgTable[size - 1][1].c_str());

	i1j1 = scoreTable[i - 1][j - 1] + atoi(mmgTable[IndexFound(sequence2[i])][IndexFound(sequence1[j]) + 1].c_str());

	if (highest < i1j1)
		highest = i1j1;

	return highest;
}

bool NeedlemanWunsch::HighestNeighbour(int positionI, int positionJ)
{

	int i;
	int j;

	if (scoreTable[positionI - 1][positionJ] + atoi(mmgTable[size - 1][1].c_str()) == scoreTable[positionI][positionJ])
	{
		i = positionI - 1;
		j = positionJ;
	}

	if (scoreTable[positionI][positionJ-1] + atoi(mmgTable[size - 1][1].c_str()) == scoreTable[positionI][positionJ])
	{
		i = positionI;
		j = positionJ - 1;
	}

	if (scoreTable[positionI - 1][positionJ - 1] + atoi(mmgTable[IndexFound(sequence2[positionI])][IndexFound(sequence1[positionJ]) + 1].c_str()) == scoreTable[positionI][positionJ])
	{
		i = positionI - 1;
		j = positionJ - 1;
	}

	tracebackPosition.push_back(i);
	tracebackPosition.push_back(j);

	if (i == 0 && j == 0)
		return false;

	HighestNeighbour(i, j);

	return true;
}

void NeedlemanWunsch::CreateOutput()
{
	string marks;
	int identity = 0;
	int similarity = 0;
	int gaps = 0;
	int vectorSize = tracebackPosition.size();
	int currentVectorPosition = vectorSize - 3;
	int j = currentVectorPosition--;
	int i = currentVectorPosition--;

	output1 = output1 + sequence1[tracebackPosition[j]];
	output2 = output2 + sequence2[tracebackPosition[i]];

	j = currentVectorPosition--;
	i = currentVectorPosition--;

	while (currentVectorPosition != -3)
	{

		if (tracebackPosition[i] == 0 && tracebackPosition[j] != 0)
		{
			output2 = output2 + '-';
			output1 = output1 + sequence1[tracebackPosition[j]];
		}
		else if (tracebackPosition[j] == 0 && tracebackPosition[i] != 0)
		{
			output1 = output1 + '-';
			output2 = output2 + sequence2[tracebackPosition[i]];
		}
		else
		{
			if (tracebackPosition[i] != tracebackPosition[i + 2])
				output2 = output2 + sequence2[tracebackPosition[i]];
			else
				output2 = output2 + '-';

			if (tracebackPosition[j] != tracebackPosition[j + 2])
				output1 = output1 + sequence1[tracebackPosition[j]];
			else
				output1 = output1 + '-';
		}

		j = currentVectorPosition--;
		i = currentVectorPosition--;
	}

	marks = output1;

	for (i = 0; i < output1.size(); i++)
	{
		if (output1[i] == '-' || output2[i] == '-')
			marks[i] = ' ';
		else if (output1[i] == output2[i])
			marks[i] = '|';
		else if (output1[i] != output2[i] && atoi(mmgTable[IndexFound(output1[i])][IndexFound(output2[i]) + 1].c_str()) <= 0)
			marks[i] = '.';
		else if (output1[i] != output2[i] && atoi(mmgTable[IndexFound(output1[i])][IndexFound(output2[i]) + 1].c_str()) > 0)
			marks[i] = ':';
	}

	for (i = 0; i < marks.size(); i++)
	{
		if (marks[i] == ' ')
			gaps++;
		else if (marks[i] == '|')
			identity++;
		else if (marks[i] == ':')
			similarity++;
	}

	similarity = similarity + identity;

	float fGaps = (float)gaps / (float)output1.size() * 100;
	float fSimilarity = (float)similarity / (float)output1.size() * 100;
	float fIdentity = (float)identity / (float)output1.size() * 100;
	float fScore = 0;

	for (i = 0; i < marks.size(); i++)
	{
		if (marks[i] == ' ')
			fScore = fScore + atoi(mmgTable[size - 1][1].c_str());
		else if (marks[i] == '|' || marks[i] == ':' || marks[i] == '.')
			fScore = fScore + atoi(mmgTable[IndexFound(output1[i])][IndexFound(output2[i]) + 1].c_str());
	
	}

	cout << "#############################################################" << endl << "#" << endl;
	cout << "#  Length:  " << output1.size() << "	(with gaps)" << endl;
	cout << "#  Identity:  " << identity << "/" << output1.size() << "	(" << fIdentity << "%)	(\"|\")" << endl;
	cout << "#  Similarity:  " << similarity << "/" << output1.size() << "	(" << fSimilarity << "%)  (\"|\" and \":\")" << endl;
	cout << "#  Gaps:  " << gaps << "/" << output1.size() << "	(" << fGaps << "%)" << endl ;
	cout << "#  Score:  " << fScore << endl << "#" << endl << "#" << endl;
	cout << "#============================================================" << endl << endl;

	int x = 1;
	int y = 50;

	while (x != output1.size())
	{

		cout << "Human		";

		for (i = x - 1; i < y; i++)
			cout << output1[i];

		cout << "	" << y << endl;

		cout << "     		";

		for (i = x - 1; i < y; i++)
			cout << marks[i];

		cout << endl;
		cout << "Mouse		";
		for (i = x - 1; i < y; i++)
			cout << output2[i];

		cout << "	" << y << endl << endl;

		x = y;
		if (y + 50 <= output1.size())
			y = y + 50;
		else
			y = output1.size();
	}
}

int NeedlemanWunsch::IndexFound(char dna)
{
	for (int i = 0; i < size; i++)
		if (mmgTable[i][0][0] == dna)
			return i;
}

NeedlemanWunsch::~NeedlemanWunsch()
{}
/*******************************
********************************
********************************
	  	 Uður Büyükyýlmaz
			040090560
********************************
********************************
*******************************/

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define m 2477

using namespace std;

string operation;

int linearCollision = 0;
int doubleCollision = 0;
int quadraticCollision = 0;

int linearDeleted = 0;
int doubleDeleted = 0;
int quadraticDeleted = 0;

int(*linearHashTable)[2] = new int[m][2];
int(*doubleHashTable)[2] = new int[m][2];
int(*quadraticHashTable)[2] = new int[m][2];
int(*copyTable)[2] = new int[m][2];

int linearProbing(int);
int doubleHashing(int);
int quadraticHashing(int);

int main()
{

	string line;
	char temp[17], keyC[8];
	int key, i, j;

	for (i = 0; i<m; i++)
	{
		for (j = 0; j<2; j++)
		{
			linearHashTable[i][j] = 0;
			doubleHashTable[i][j] = 0;
			quadraticHashTable[i][j] = 0;
			copyTable[i][j] = 0;
		}
	}

	ifstream input("dataset.txt");

	while (!input.eof())
	{
		getline(input, line);
		j = 0;

		while (line[j] != ':')
		{
			temp[j] = line[j];
			j++;
		}

		j++;
		i = 0;

		while (line[j] != '\0')
		{
			keyC[i++] = line[j++];
		}

		operation = temp;
		key = atoi(keyC);

		linearProbing(key);
		doubleHashing(key);
		quadraticHashing(key);

		operation = "";
		memset(temp, 0, 17);
		memset(keyC, 0, 8);
	}

	input.close();

	cout << endl << "***********************************************************" << endl << endl;
	cout << "Linear Probing: " << linearCollision << " collusions have been occurred." << endl;
	cout << "Double Hashing: " << doubleCollision << " collusions have been occurred." << endl;
	cout << "Quadratic Hashing: " << quadraticCollision << " collusions have been occurred." << endl;

	return 0;
}

int linearProbing(int key)
{

	int i = 0, h;

	if (operation == "insert")
	{
		while (i != m)
		{
			h = (key + i) % m;

			if (linearHashTable[h][1] == 0 || linearHashTable[h][1] == -1)
			{
				if (linearHashTable[h][1] == -1)
					linearDeleted--;

				linearHashTable[h][0] = key;
				linearHashTable[h][1] = 1;

				cout << "Insertion: Key " << key << " is inserted in index " << h << " of linear hash table." << endl;

				return 0;
			}
			else
			{
				linearCollision++;
				i++;
			}
		}
	}
	else if (operation == "delete")
	{
		i = 0;

		while (i != m)
		{
			h = (key + i) % m;

			if (linearHashTable[h][0] == key && linearHashTable[h][1] == 1)
			{
				linearHashTable[h][1] = -1;
				linearDeleted++;

				cout << "Deletion: Key " << key << " is deleted from the linear hash table." << endl;

				if (linearDeleted > 50)
				{
					cout << "Linear collisions is set to zero." << endl;
					cout << "Linear hash table is being rehashed..." << endl;
					linearCollision = 0;

					for (int j = 0; j<m; j++)
					{
						for (int k = 0; k<2; k++)
						{
							copyTable[j][k] = linearHashTable[j][k];
							linearHashTable[j][k] = 0;
						}
					}

					for (int j = 0; j<m; j++)
					{
						if (copyTable[j][1] == 1)
						{
							operation = "insert";
							linearProbing(copyTable[j][0]);
						}
					}

					linearDeleted = 0;
					operation = "delete";
					cout << "Linear hash table is rehashed." << endl;
				}
				return 0;
			}
			else
			{
				i++;
			}
		}

		cout << "Deletion: Key " << key << " is not found in the linear hash table." << endl;
		return -1;
	}
	else if (operation == "retrieve")
	{

		i = 0;
		while (i != m)
		{
			h = (key + i) % m;

			if (linearHashTable[h][0] == key && linearHashTable[h][1] == 1)
			{
				cout << "Retrieve: Key " << key << " is found at index " << h << " in the linear hash table." << endl;
				return h;
			}
			else
			{
				i++;
			}
		}

		cout << "Retrieve: Key " << key << " is not found in the linear hash table." << endl;
		return -1;
	}

	return 0;
}

int doubleHashing(int key)
{
	int i = 0, h, h1, h2;

	if (operation == "insert")
	{
		while (i != m)
		{
			h1 = key % m;
			h2 = 1 + (key % (m - 4));
			h = (h1 + i * h2) % m;

			if (doubleHashTable[h][1] == 0 || doubleHashTable[h][1] == -1)
			{
				if (doubleHashTable[h][1] == -1)
					doubleDeleted--;

				doubleHashTable[h][0] = key;
				doubleHashTable[h][1] = 1;

				cout << "Insertion: Key " << key << " is inserted in index " << h << " of double hash table." << endl;

				return 0;
			}
			else
			{
				doubleCollision++;
				i++;
			}
		}
	}
	else if (operation == "delete")
	{
		i = 0;
		while (i != m)
		{
			h1 = key % m;
			h2 = 1 + (key % (m - 4));
			h = (h1 + i * h2) % m;

			if (doubleHashTable[h][0] == key && doubleHashTable[h][1] == 1)
			{
				doubleHashTable[h][1] = -1;
				doubleDeleted++;

				cout << "Deletion: Key " << key << " is deleted from the double hash table." << endl;

				if (doubleDeleted > 50)
				{
					cout << "Double collisions is set to zero." << endl;
					cout << "Double hash table is being rehashed..." << endl;
					doubleCollision = 0;

					for (int j = 0; j<m; j++)
					{
						for (int k = 0; k<2; k++)
						{
							copyTable[j][k] = doubleHashTable[j][k];
							doubleHashTable[j][k] = 0;
						}
					}

					for (int j = 0; j<m; j++)
					{
						if (copyTable[j][1] == 1)
						{
							operation = "insert";
							doubleHashing(copyTable[j][0]);
						}
					}

					doubleDeleted = 0;
					operation = "delete";
					cout << "Double hash table is rehashed." << endl;
				}
				return 0;
			}
			else
			{
				i++;
			}
		}

		cout << "Deletion: Key " << key << " is not found in the double hash table." << endl;
		return -1;
	}
	else if (operation == "retrieve")
	{
		i = 0;
		while (i != m)
		{
			h1 = key % m;
			h2 = 1 + (key % (m - 4));
			h = (h1 + i * h2) % m;

			if (doubleHashTable[h][0] == key && doubleHashTable[h][1] == 1)
			{
				cout << "Retrieve: Key " << key << " is found at index " << h << " in the double hash table." << endl;
				return h;
			}
			else
			{
				i++;
			}
		}

		cout << "Retrieve: Key " << key << " is not found in the double hash table." << endl;
		return -1;
	}
}

int quadraticHashing(int key)
{
	int i = 0, h, h1;

	if (operation == "insert")
	{
		while (i != m)
		{
			h1 = key%m;
			h = (h1 + i + 2 * i*i) % m;

			if (quadraticHashTable[h][1] == 0 || quadraticHashTable[h][1] == -1)
			{
				if (quadraticHashTable[h][1] == -1)
					quadraticDeleted--;

				quadraticHashTable[h][0] = key;
				quadraticHashTable[h][1] = 1;

				cout << "Insertion: Key " << key << " is inserted in index " << h << " of quadratic hash table." << endl;

				return 0;

			}
			else
			{

				quadraticCollision++;
				i++;
			}
		}
	}
	else if (operation == "delete")
	{
		i = 0;
		while (i != m)
		{
			h1 = key%m;
			h = (h1 + i + 2 * i*i) % m;

			if (quadraticHashTable[h][0] == key && quadraticHashTable[h][1] == 1)
			{
				quadraticHashTable[h][1] = -1;
				quadraticDeleted++;

				cout << "Deletion: Key " << key << " is deleted from the quadratic hash table." << endl;

				if (quadraticDeleted > 50)
				{
					cout << "Quadratic collisions is set to zero." << endl;
					cout << "Quadratic hash table is being rehashed..." << endl;
					quadraticCollision = 0;

					for (int j = 0; j<m; j++)
					{
						for (int k = 0; k<2; k++)
						{
							copyTable[j][k] = quadraticHashTable[j][k];
							quadraticHashTable[j][k] = 0;
						}
					}

					for (int j = 0; j<m; j++)
					{
						if (copyTable[j][1] == 1)
						{
							operation = "insert";
							quadraticHashing(copyTable[j][0]);
						}
					}

					quadraticDeleted = 0;
					operation = "delete";

					cout << "Quadratic hash table is rehashed." << endl;
				}
				return 0;
			}
			else
			{
				i++;
			}
		}

		cout << "Deletion: Key " << key << " is not found in the quadratic hash table." << endl;
		return -1;
	}
	else if (operation == "retrieve")
	{
		i = 0;
		while (i != m)
		{
			h1 = key%m;
			h = (h1 + i + 2 * i*i) % m;;

			if (quadraticHashTable[h][0] == key && quadraticHashTable[h][1] == 1)
			{
				cout << "Retrieve: Key " << key << " is found at index " << h << " in the quadratic hash table." << endl;
				return h;
			}
			else
			{
				i++;
			}
		}

		cout << "Retrieve: Key " << key << " is not found in the quadratic hash table." << endl;
		return -1;
	}
}

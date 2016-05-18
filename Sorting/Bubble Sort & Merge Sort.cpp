#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<time.h>

using namespace std;

clock_t start, difference;

void input(int [], int);
void output(int [], int);
void BubbleSort(int [], int);
void DivideAndConquer(int, int, int, int [], int);
void MergeSort(int, int, int [], int);


int main(int argc, char** argv)
{	
	char type=argv[1][0];
	const int N = atoi(argv[2]);
	int data[N];

	if (type == 'b' || type == 'B')
	{
		BubbleSort(data, N);
		output(data, N);	
	}
	else if (type == 'm' || type == 'M')
		{
			input(data, N);
			cout<<"Merge Sort is working..."<<endl;
			start = clock();
			MergeSort(0, N-1, data, N);
			difference = clock() - start;
			output(data, N);
		}
	else
		cout<<"Wrong Format!"<<endl;	

	cout<<"runing time: "<<((float)difference)/CLOCKS_PER_SEC<<" seconds"<<endl;
	
	return 0;
}

void input(int data[], int N)
{
	ifstream input("data.txt");

	for (int i = 0; i<N; i++)
	{
		input >> data[i];
	}

	input.close();

	cout<<"============================="<<endl<<"data.txt is read!"<<endl;
}

void output(int data[], int N)
{
	ofstream output("sorted.txt");

	for (int i = 0; i < N; i++)
	{
		output << data[i] << endl;
	}
	output.close();

	cout<<"sorted.txt is created!"<<endl<<"============================="<<endl;
}

void BubbleSort(int data[], int N)
{
	int temp;

	input(data, N);

	cout<<"Bubble Sort is working..."<<endl;

	start = clock();

	for (int i = 0; i < N-1; i++)
	{
		for (int j = 0; j < N-i-1; j++)
		{
			if (data[j] > data[j+1])
			{
				temp = data[j + 1];
				data[j + 1] = data[j];
				data[j] = temp;
			}
		}
	}
	difference = clock() - start;
	cout<<"Bubble Sort is done!"<<endl;	
}


void DivideAndConquer(int bottom,int mid,int top, int data[], int N)
{
	int h, i, j, k, buffer[N];

	h = bottom;
	i = bottom;
	j = mid + 1;

	while((h <= mid) && (j <= top))
	{
	  if(data[h] <= data[j])
	  {
		   buffer[i] = data[h];
		   h++;
	  }
	  
	  else
	  {
		   buffer[i] = data[j];
		   j++;
	  }
	  
	  i++;
	}
	
	if(h > mid)
	{
	  for(k=j; k <= top; k++)
	  {
		   buffer[i] = data[k];
		   i++;
	  }
	}
	
	else
	{
	  for(k=h; k <= mid; k++)
	  {
		   buffer[i] = data[k];
		   i++;
	  }
 	}
 
	for(k=bottom ; k<=top ; k++) 
		data[k] = buffer[k];	 
}

void MergeSort(int bottom,int top, int data[], int N)
{
	int mid;
	
	if(bottom < top)
	{
		mid = (bottom + top) / 2;
		MergeSort(bottom, mid, data, N);
		MergeSort(mid+1, top, data, N);
		DivideAndConquer(bottom, mid, top, data, N);
	}
}





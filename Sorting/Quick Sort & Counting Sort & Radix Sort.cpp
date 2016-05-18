/************************************************
*************************************************
			Uğur Büyükyılmaz
				040090560
**************************************************
*************************************************/


#include<iostream>
#include<fstream>
#include<time.h>
#include<math.h>

using namespace std;

void quickSort(int *, int, int);
int partition(int *, int, int);
void countingSort(int *, int);
void radixSort(int *, int);

int main(int argc, char** argv){
	
	char algorithm_type = argv[1][0];
	string input_file = argv[2];
	int *array;
	int i=-1;
	int temp;
	clock_t start, difference;

	ifstream inputTemp(input_file.c_str());		// the standard streams does not accept a standard string, only c-string
	
	while(!inputTemp.eof())
		{
		inputTemp>>temp;
		i++;
		}
		
	inputTemp.close();		
							
	const int array_size = i;
	
	array = new int [array_size];
	
	ifstream input(input_file.c_str());  
	
	for (i = 0; i<array_size; i++)
			input >> array[i];

	input.close();
	
	start = clock();
		
	switch (algorithm_type)
	{
		case 'q':
			quickSort(array, 0, array_size-1);
			difference = clock() - start;
			break;
		case 'c':
			countingSort(array, array_size);
			difference = clock() - start;
			break;
		case 'r':
			radixSort(array, array_size);
			difference = clock() - start;
			break;
		default:
			cout<<"Wrong format! Please enter 'q', 'c' or 'r'"<<endl;
			difference = clock() - start;
			break;
	}
	
	cout<<((float)difference)/CLOCKS_PER_SEC<<" seconds"<<endl;

	return 0;

}

void quickSort(int *array, int first, int last)
{
		
		int boundary;
	
		if(first < last)
		{
			boundary = partition(array, first, last);
			quickSort(array, first, boundary-1);
			quickSort(array, (boundary + 1), last);
		}
}

int partition(int *array, int first, int last)
{
	
	int pivot, boundary, temp;
	
	pivot = array[last];
	boundary = first;
	
	for(int i=first; i<last; i++)
	{
		if(array[i]<=pivot)
		{
			temp=array[i];
			array[i]=array[boundary];
			array[boundary]=temp;
			boundary++;
		}	
	}
	
	temp=array[boundary];
	array[boundary]=array[last];
	array[last]=temp;	
	
	return boundary;
}

void countingSort(int *array, int array_size)
{
		int *tempArray; 
		tempArray=new int[array_size];
		int i;
		int tempMax=array[0];
		
		for(i=1; i<array_size;i++)
			tempMax = array[i] > tempMax ? array[i] : tempMax; 
			
		const int max = tempMax;
		
		int *countsArray;
		countsArray = new int[max+1];
		
		for(i=0; i<max+1;i++)
			countsArray[i]=0;
			
		for(i=0; i<array_size; i++)
			countsArray[array[i]] = countsArray[array[i]] + 1;
			
		for(i=1; i<max+1; i++)
			countsArray[i] = countsArray[i] + countsArray[i-1];
			
		for(i=array_size-1; i>=0; i--)
		{
			tempArray[countsArray[array[i]]-1] = array[i];
			countsArray[array[i]]--;	
		}
			
		for(i=0; i<array_size;i++)
			array[i]=tempArray[i];
}

void radixSort(int *array, int array_size)
{
		int Max=array[0], i, j, k, flag, d=0, a=1;
		int *digitArray;
		digitArray = new int [array_size];
		int *tempArray;
		tempArray= new int [array_size];
		
		for(i=1; i<array_size;i++)
			Max = array[i] > Max ? array[i] : Max;		// Max value in array
			
		d=log10(Max)+1;
		
		while(d>0)
		{
			
			for(k=0; k<array_size; k++)
				digitArray[k]=((array[k] % (a*10)) / a);
			
			countingSort(digitArray, array_size);
			
			i=0;
			j=0;
			k=0;
			flag=0;
			
			while(i != array_size)
			{
				if(digitArray[i]==((array[j] % (a*10)) / a))
				{
					tempArray[k]=array[j];
					k++;
					i++;
					flag=1;
				}
				
				j++;
				
				if(i != 0 && i != array_size && digitArray[i] != digitArray[i-1] && flag==1)
				{
					j=0;
					flag=0;
				}		
			}	
				
			for(k=0; k<array_size; k++)
				array[k]=tempArray[k];
				
			a*=10;
			d--;
		}
}

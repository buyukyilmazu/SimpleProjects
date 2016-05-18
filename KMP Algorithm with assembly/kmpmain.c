#include<stdio.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_TEXT_LENGTH 5000
#define MAX_PATTERN_LENGTH 5000

int kmp(char *text, char *searchString);

int main(void)
{

	char fileName[MAX_FILENAME_LENGTH];
	char text[MAX_TEXT_LENGTH];
	char searchString[MAX_PATTERN_LENGTH];

	int i = 0;
	FILE *fptr;

	printf("Please enter the file name: ");
	scanf("%s", fileName);

	fptr = fopen(fileName, "r");
	
	if(!fptr) 
	{
		printf("File could not be opened!\n");
		return 1;
	}

	while(!feof(fptr))
	{	
		text[i++] = fgetc(fptr);
	}
	
	fclose(fptr);

	printf("Please enter the search string: ");
	scanf("%s", searchString);
	
	int result = kmp(text, searchString);
	result == -1 ? printf("\nFailed to find pattern in the text.\n")
				 : printf("\nFound pattern at index: %d\n", result);

	return 0;
}

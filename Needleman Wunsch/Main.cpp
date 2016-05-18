#include "NeedlemanWunsch.h"

int main(){

	NeedlemanWunsch globalAlignment;

	globalAlignment.ReadFile();
	globalAlignment.CreateScoreTable();
	globalAlignment.CreateOutput();


	return 0;
}
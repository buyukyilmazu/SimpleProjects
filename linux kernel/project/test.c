#include <stdio.h>
#include <unistd.h>
#define NR_mycall 351

int main (void){
	
     int x1, x2, y;
     printf("Please enter the processID and flag number:\n");
     scanf("%d%d",&x1,&x2);
     y = syscall(NR_mycall, x1, x2);
	 printf("ProcessID=%d  flag number=%d\n",x1,y);
     return 0 ;
}

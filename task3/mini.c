#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	float inputx;
	int check = 5;

	do
	{
		if(check < 5){
			fflush(stdin);
			printf("\n error invald number" );
			printf("\n enter again: " );
			check = scanf("\n %f",&inputx);
		}
		else{
			printf("\nplease enter a number: ");
			check = scanf("\n %f",&inputx);
		}

	}while(check != 1);

	printf("\n your number is %f",inputx);
}
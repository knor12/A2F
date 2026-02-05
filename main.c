#include <stdio.h>
#include <stdlib.h>
#include "a2f.h" 


int main(int argc, char *argv[]){
	
	float f = 0.0; 
	int ret;
	const char *strings[] = {  
		"912.5312",
		"123.7852",
		"0.93568",
		"N912.5312",
		"",
		"2..1",
		".568989",
		"45235.k",
		"58693"
	};
	
	size_t count = sizeof(strings) / sizeof(strings[0]);
	size_t i = 0;
	for (i = 0; i < count; i++){
		printf("\nTrying to parse %s \n", strings[i]);
		f = 0.0;
		ret = A2F_GetFloat(&f, strings[i]);
		printf("Result=%f , Error Code=%d \n" , f , ret );
	}
	
	

	return 0;	
}




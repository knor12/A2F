#include <stdio.h>
#include <stdlib.h>
#include "a2f.h" 


int main(int argc , char * argv[]){
	
	float f =0.0; 
	int ret ;
	char *  string[10][10]={  
		{"912.5312"},
		{"123.7852"},
		{"0.93568"},
		{"N912.5312"},
		{""},
		{"2..1"},
		{".568989"},
		{"45235.k"},
		{"58693"}
	};
	
	int i =0;
	for (i=0; i<9;i++){
		printf("\nTrying to parse %s \n" ,string[i][0]  );
		f=0.0;
		ret =  A2F_GetFloat(&f, string[i][0] );
		printf("Result=%f , Error Code=%d \n" , f , ret );
	}
	
	

	return 0;	
}




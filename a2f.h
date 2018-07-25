#ifndef A2F_H
#define A2F_H
#include <stdio.h>
#include <stdlib.h>

//#define A2F_DEBUG 1

#define A2F_SUCCESS 0
#define A2F_FAILURE -1 


/*This is the only publicly available function of this module
*Input string: a char pointer to a string of integer or float , 
*output result: a float pointer value of the parsed string supplied by string.
*output returned: equals A2F_SUCCESS on success, otherwise A2F_FAILURE.  
*/
int A2F_GetFloat(float * result, char * string);


#endif /* A2F_H */
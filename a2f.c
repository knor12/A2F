#include "a2f.h"



/*Private
This enumerator hold all the possible states of the finite state machine*/
typedef enum {
    A2F_State_Integer,
    A2F_State_Decimal,
    A2F_State_Error,
    A2F_State_Finished
}A2F_State_t;


/*
*Private
*To assure re-entrancy of the code this data structure is used to hold all the relevant data of a parse job
*This a private data structure not accessible outside the module
*/
typedef struct{
    char * A2F_string;
    float A2F_Result;
    float A2F_Decimal_Position;
    A2F_State_t current_state;
} A2F_t;



/*private function to initializes the parser data structure */
static void a2f_Init(A2F_t * state_machine  , char * string){
    
    state_machine->A2F_string = string;
    state_machine->A2F_Result =0.0;
    state_machine->A2F_Decimal_Position=1.0;
    state_machine->current_state = A2F_State_Integer;  
}


/*
*Private function implements the logic of the algorithm.  
*Refer to the finite state machine below for an explanation of the algorithm.
* The below state machine summarizes  the algorithm used to to parse a string of a float or a string of an integer into a float  
                                        +-------------------+                                      
                                        | +---------------+ |                                      
                                        | |    Start      | |                                      
                                        | |               | |                                      
                                        | +---------------+ |                                      
                                        +-------------------+                                      
                                                  |                                                
                                                  | Init                                           
                                                  |                                                
                                                  |                                                
+---------+                                       v             IsDigit                            
|         |                                  +--------+-------------+                              
| Errror  |        Else                      |        |             |                              
|         |<-------------------------------- |Integer | <------------                +-----------+ 
+---------+                                  |        | ---------------------------->|  Finished | 
    ^                                        +--------+           IsNUll             |           | 
    |                                                                                +-----------+ 
    |                                             |                                        ^       
    |                                             |                                        |       
    |                                             |IsPoint                                 |       
    |                                             |                                        |       
    |                                             |                                        |       
    |                                             v                                        |       
    |                                                          IsDigit                     |       
    |                                       +--------+ ------------+                       |       
    |                                       |        |             |                       |       
    +------------------------------------   |Decimal | <---------- +                       |       
             Else                           |        |                                     |       
                                            +--------+   ----------------------------------+       
                                                                    IsNull                    
*/

static A2F_State_t a2f_InsetChar(A2F_t * state_machine  ){
    
    
#ifdef A2F_DEBUG

printf("Current value %f \n ." , state_machine->A2F_Result);
printf("Current State %d \n ." , state_machine->current_state);

#endif     
    
    
    char * str = state_machine->A2F_string;
    
    switch (state_machine->current_state){
        case A2F_State_Integer:
            switch(* str){
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state_machine->A2F_Result = state_machine->A2F_Result*10.0+  (float)((*str)-'0');
                    break;        
                case '.': 
                    state_machine->current_state =A2F_State_Decimal;
                    break;
                case 0:    
                    state_machine->current_state =A2F_State_Finished;
                    break;
                default: 
                    state_machine->current_state =A2F_State_Error;
                    break;        
            }
            break;
        case A2F_State_Decimal:
            switch(* str){
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state_machine->A2F_Decimal_Position/=10.0;
                    state_machine->A2F_Result = state_machine->A2F_Result +  ((*str )-'0')*state_machine->A2F_Decimal_Position;
#ifdef A2F_DEBUG

printf("decimal addition %f \n ." , ((*str )-'0')*state_machine->A2F_Decimal_Position);

#endif
                    break;
                case 0:    
                    state_machine->current_state =A2F_State_Finished;
                    break;                    
                default: 
                    state_machine->current_state =A2F_State_Error;
                    break;        
            }
            break;
        case A2F_State_Error:
            break;
        default:
            state_machine->current_state =A2F_State_Error;        
    }
    state_machine->A2F_string+=1;
    return state_machine->current_state; 
}


/*
*This is the only  public function of the whole module, it gets a string and return the value of the parsed float by reference
*it returns A2F_SUCCESS on success, otherwise it is a A2F_FAILURE. 
*/
int A2F_GetFloat(float * result, char * string){
    
    A2F_State_t state; 
    A2F_t A2F_temp;
    a2f_Init(&A2F_temp  ,  string);
    
    do {
		
        state = a2f_InsetChar(&A2F_temp); 
		
    }while(!(state==A2F_State_Error || state==A2F_State_Finished ));
    
    if (state==A2F_State_Finished){
		
        *result = A2F_temp.A2F_Result;
        return A2F_SUCCESS;
		
    }else {
        return A2F_FAILURE;
    }
    
    
}
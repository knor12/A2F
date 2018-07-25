# A2F

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

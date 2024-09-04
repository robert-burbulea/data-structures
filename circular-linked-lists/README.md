Based on the commands [1] given as input, the program simulates a train mechanic that can create or delete train wagons, move between them and write data into them.

The train is represented as a circular linked list where the mechanic is a pointer to his current location.

Some commands are executed directly, while others are saved into a queue. If the string "EXECUTE" appears in the input file, the oldest command will be executed.


[1]
void PrintList(Train *t);
void IntrCell_Right(Train *p_Train, char elem);
void IntrCell_Left(Train *p_Train, char elem);
void MOVE_LEFT(Train *p_Train);
void MOVE_RIGHT(Train *p_Train);
void WRITE(Train *p_Train, char elem);
void CLEAR_CELL(Train *p_Train);
int Initial_state(Train *p_Train);
void CLEAR_ALL(Train *p_Train);
void INSERT_LEFT(FILE *out, Train *p_Train, char elem);
void INSERT_RIGHT(Train *p_Train, char elem);
void SHOW_CURRENT(FILE *out, Train *p_Train);
void SHOW(FILE *out, Train *p_Train);
#include "list.h"
#include "queue.h"
#include <string.h>
#include <stdio.h>


void EXECUTE(FILE *out, Train *p_Train, TQueue *queue, int *direction) {
    char *line = (char *)malloc(sizeof(char*));

    if ( (*direction) == 1) {
        ExtrQ(queue, line);
    } else {
        ExtrQ_Switched(queue, line);
    }

    char *command = strtok(line, " \n");
    char *character = strtok(NULL, "\n");

    if (strcmp(command, "MOVE_LEFT") == 0) {
        MOVE_LEFT(p_Train);
    } else if (strcmp(command, "MOVE_RIGHT") == 0) {
        MOVE_RIGHT(p_Train);
    } else if (strcmp(command, "CLEAR_CELL") == 0) {
        CLEAR_CELL(p_Train);
    } else if (strcmp(command, "CLEAR_ALL") == 0) {
        CLEAR_ALL(p_Train);
    } else if (strcmp(command, "WRITE") == 0) {
        WRITE(p_Train, character[0]);
    } else if (strcmp(command, "INSERT_LEFT") == 0) {
        INSERT_LEFT(out, p_Train, character[0]);
    } else if (strcmp(command, "INSERT_RIGHT") == 0) {
        INSERT_RIGHT(p_Train, character[0]);
    }
    free(line);
}

void Call_Command(FILE *out, char *line, Train *p_Train, TQueue *queue, int *direction) {
    char *command = strtok(line, "\n");
    if (strcmp(command, "SHOW_CURRENT") == 0) {
        SHOW_CURRENT(out, p_Train);
    } else if (strcmp(command, "SHOW") == 0) {
        SHOW(out, p_Train);
    } else if (strcmp(command, "EXECUTE") == 0) {
        EXECUTE(out, p_Train, queue, direction);
    } else if (strcmp(command, "SWITCH") == 0) {
        (*direction) *= -1;
    } else {
        IntrQ(queue, command);
    }
}

void citeste(FILE *in, FILE *out, Train *p_Train, TQueue *queue, int *direction) {
    char *line = NULL;
    size_t len = 0;
    int N;

        // Read the first line
    if (getline(&line, &len, in) != -1) {
        // Parse the integer from the line
        if (sscanf(line, "%d", &N) != 1) {
            fprintf(stderr, "Error parsing integer\n");
            fclose(in);
            free(line);
            return;
        }
    } else {
        fprintf(stderr, "Error reading file\n");
        fclose(in);
        return;
    }
    int i;
    for (i = 0; i < N && (getline(&line, &len, in) != -1); i++) {
        Call_Command(out, line, p_Train, queue, direction);
    }
    // Clean up
    free(line);
}

int main(){
    FILE *in, *out;
    char *input_file_name, *output_file_name;

    // in = fopen("Tests/Input/test15.in", "rt");
    in = fopen("circular-linked-list.in", "rt");
    if (in == NULL) {
        perror("Error opening file");
        fclose(in);
        return 1;
    }
    out = fopen("circular-linked-list", "wt");
    if (out == NULL) {
        perror("Error opening output file");
        fclose(out);
        return 1;
    }

    Train *p_Train = InitTrain();
    TQueue *queue = InitQ();
    int direction = 1;
    citeste(in, out, p_Train, queue, &direction);

    fclose(in);
    fclose(out);

    return 0;
}


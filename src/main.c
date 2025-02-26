
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



typedef struct input_buffer {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;

} INPUT_BUFFER_T;

INPUT_BUFFER_T* new_input_buffer() {
    INPUT_BUFFER_T* input_buffer = malloc(sizeof(INPUT_BUFFER_T));

    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void read_input(INPUT_BUFFER_T *input_buffer) {
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if(bytes_read <= 0) {
        printf("stdin read error\n");
        exit(EXIT_FAILURE);
    }

    // Ignore trailign newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = '\0';
}

void close_input_buffer(INPUT_BUFFER_T *input_buffer) {
    if(input_buffer != NULL) {
        free(input_buffer->buffer);
        free(input_buffer);
    }
}

void print_prompt() {
    printf("db > ");
}


typedef enum meta_command_result {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} META_COMMAND_RESULT_T;

typedef enum prepare_result {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PREPARE_RESULT_T;

typedef enum statement_type {
    STATEMENT_INSERT,
    STATEMENT_SELECT,
    STATEMENT_DELETE
} STATEMENT_TYPE_T;

typedef struct statement {
    STATEMENT_TYPE_T type;
} STATEMENT_T;

META_COMMAND_RESULT_T do_meta_command(INPUT_BUFFER_T *input_buffer) {
    if(strcmp(input_buffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
    }
    else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PREPARE_RESULT_T prepare_statement(INPUT_BUFFER_T *input_buffer, STATEMENT_T *statement) {
    if(strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    else if(strncmp(input_buffer->buffer, "select", 6) == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    else if(strncmp(input_buffer->buffer, "delete", 6) == 0) {
        statement->type = STATEMENT_DELETE;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(STATEMENT_T *statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            {
                printf("We are doing an insert.\n");
            }
            break;
        case (STATEMENT_SELECT):
            {
                printf("We are doing an select.\n");
            }
            break;
        case (STATEMENT_DELETE):
            {
                printf("We are doing an delete.\n");
            }
            break;
        default:
            {
                printf("If you reached this, something is very wrong.\n");
            }
            break;
    }
}

int main(int argc, char *argv[]) {
    INPUT_BUFFER_T *input_buffer = new_input_buffer();

    while(true) {
        print_prompt();
        read_input(input_buffer);

        if(input_buffer->buffer[0] == '.') {
            switch(do_meta_command(input_buffer)) {
                case (META_COMMAND_SUCCESS):
                    {
                        continue;
                    }
                    break;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    {
                        printf("Unrecognized command '%s'\n", input_buffer->buffer);
                        continue;
                    }
                    break;
            }
        }

        STATEMENT_T statement;
        switch(prepare_statement(input_buffer, &statement)) {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                {
                    printf("Unrecognized keyword at start of '%s'\n", input_buffer->buffer);
                    continue;
                }
                break;
        }

        execute_statement(&statement);
        printf("Executed\n");

    }

    close_input_buffer(input_buffer);
    exit(EXIT_SUCCESS);

}

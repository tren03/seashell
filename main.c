#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSH_RL_BUFSIZE 1024

// read a line into a array and return array
char *lsh_read_line(void) {
    // initial memory size of buffer
    int bufsize = LSH_RL_BUFSIZE;

    // initial array position
    int position = 0;

    // allocation of memory for buffer
    char *buffer = malloc(sizeof(char) * bufsize);

    // we store chars in buffer as ascii values since EOF(-1) is not a char
    int c;

    // exit if buffer creation fails
    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    // reading a single line - can be done with getline() too, this is for more
    while (1) {

        // read single char as int -> ascii value
        c = getchar();

        /* if c is EOF of \n, we append nullchar to end of buffer which signals
         end of string(there is no built in strings in C) and return buffer with
         the line else we add char read to buffer at specified position and
         increment position */
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';

            // debug statements
            /* int pstatus = printf("%s", buffer); */
            /* printf("\n%d\n", pstatus); */

            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // if buffer size exceeds initially assumed size, increase it.
        if (position > bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


// initial size of token array
#define LSH_TOK_BUFSIZE 64

// all the delimiters
#define LSH_TOK_DELIM " \t\r\n\a"

// splits the line into multiple tokens and returns the token array (2D) where is token is also an array
char **lsh_split_line(char *line) {


    /* printf("LINE RECIEVED : %s\n", line); */
    int buffsize = LSH_TOK_BUFSIZE;
    int position = 0;

    // we store \0 at the end of each entry of tokens (that is why we use char*)
    char **tokens = malloc(sizeof(char *) * buffsize);
    char *token;

    // err incase token array initialization fails
    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    // tokenize only till you reach first delimiter
    token = strtok(line, LSH_TOK_DELIM);

    while (token != NULL) {
        tokens[position] = token;
        position++;

        // prints out all the tokens
        /* printf("TOKENS : %s\n", token); */

        // we have more number of tokens than initally assumed [64]
        if (position >= buffsize) {
            buffsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, buffsize);
            if (!tokens) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        // continue tokenizing from where you left off previously
        token = strtok(NULL, LSH_TOK_DELIM);
    }

    tokens[position] = NULL;

    
    return tokens;
}

void lsh_loop(void) {
    // array of chars
    char *line;

    // array of args of char ? why is it 2d
    char **args;
    int status;

    do {
        printf("> ");
        
        // get a line
        line = lsh_read_line();

        // split given line into tokens
        args = lsh_split_line(line);
        /* status = lsh_execute(args); */

        free(line);
        free(args);
    } while (status);
}

int main(int argc, char *argv[]) {
    lsh_loop();
    printf("%s\n", "finished");
    return EXIT_SUCCESS;
}

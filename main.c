#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void) {
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            /* int pstatus = printf("%s", buffer); */
            /* printf("\n%d\n", pstatus); */
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

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

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **lsh_split_line(char *line) {
    printf("LINE RECIEVED : %s\n", line);
    int buffsize = LSH_TOK_BUFSIZE;
    int position = 0;

    // we store \0 at the end of each entry of tokens (that is why we use char*)
    char **tokens = malloc(sizeof(char *) * buffsize);
    char *token;

    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    // tokenize only till you reach first delimiter
    token = strtok(line, LSH_TOK_DELIM);

    while (token != NULL) {
        tokens[position] = token;
        position++;

        printf("TOKENS : %s\n", token);

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
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = lsh_read_line();
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

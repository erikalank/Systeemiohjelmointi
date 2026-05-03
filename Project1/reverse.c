#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *args[]) {
    // Check for too many arguments
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    FILE *input_file = stdin;
    FILE *output_file = stdout;
    // Open input file if provided
    if (argc >= 2) {
        input_file = fopen(args[1], "r");
        if (input_file == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", args[1]);
            exit(1);
        }
    }
    // Open output file if provided
    if (argc == 3) {
        if (strcmp(args[1], args[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }
        output_file = fopen(args[2], "w");
        if (output_file == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", args[2]);
            exit(1);
        }
    }

    

    char *line = NULL;
    size_t len = 0;
    char **lines = NULL;
    int line_count = 0;
    // Read all lines
    while (getline(&line, &len, input_file) != -1) {

        char **tmp = realloc(lines, (line_count + 1) * sizeof(char *));
        if (tmp == NULL) {
            fprintf(stderr, "malloc failed\n");
            free(line);
            fclose(input_file);
            return 1;
        }

        lines = tmp;

        lines[line_count] = malloc(strlen(line) + 1);

        if(lines[line_count] == NULL) {
            fprintf(stderr, "malloc failed\n");
            free(line);
            fclose(input_file);
            return 1;
        }

        
        strcpy(lines[line_count], line);
        line_count++;
    }
    // Write lines in reverse order
    for (int i = line_count - 1; i >= 0; i--) {
        fprintf(output_file, "%s", lines[i]);
        free(lines[i]);
    }
    
    // Clean up
    free(lines);
    free(line); 
    if (output_file != stdout) {
        fclose(output_file);
    }
    if (input_file != stdin) {
        fclose(input_file);
    }
    return 0;
    
}
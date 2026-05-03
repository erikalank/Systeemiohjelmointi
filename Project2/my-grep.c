#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // No search term, exit
    if(argc < 2) {
        printf("my-grep: searchterm [file ...]\n");
        return 1;
    }

    char *pattern = argv[1];
    
    if (argc == 2) {
        // Read from stdin
        char *line = NULL;
        size_t line_len = 0;
        while (getline(&line, &line_len, stdin) != -1) {
            if (strstr(line, pattern) != NULL) {
                printf("%s", line);
            }
        }
        free(line);
        return 0;
    }
    // Loop through files and search for pattern
    for(int i = 2; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("my-grep: cannot open file\n");
            return 1;
        }
        char *line = NULL;
        size_t line_len = 0;
        // Print lines containing the pattern
        while (getline(&line, &line_len, file) != -1) {
            if (strstr(line, pattern) != NULL) {
                printf("%s", line);
            }
        }
        free(line);
        fclose(file);
    }
    return 0;
}
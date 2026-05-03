#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    //No files, exit
    if(argc == 1) {
        return 0; 
    }
    // Read all files given in the command line
    for(int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        // If file cannot be opened, print error and exit
        if (file == NULL) {
            printf("my-cat: cannot open file\n");
            return 1;
        }
        char line[1024];
        // Read and print each line of the file
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }
       
        fclose(file);
    }
    return 0;
}
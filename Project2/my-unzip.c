#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if at least one file is provided
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    FILE * file;
    int count;
    char character;

    // Loop through each file provided in the command line
    for (int i = 1; i < argc; i++) {
        file = fopen(argv[i], "r");
        // If file cannot be opened, print error and exit
        if (file == NULL) {
            printf("my-unzip: cannot open file\n");
            return 1;
        }

        // Read the count and character pairs from the file and print the uncompressed output
        while (fread(&count, sizeof(int), 1, file) == 1 && fread(&character, sizeof(char), 1, file) == 1) {
            for (int j = 0; j < count; j++) {
                printf("%c", character);
            }
        }
        fclose(file);
    }

    return 0;
}
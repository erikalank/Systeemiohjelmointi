#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if at least one file is provided
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        return 1;
    }

    FILE * file;
    char current, previous;
    int count;

    // Loop through each file provided in the command line
    for (int i = 1; i < argc; i++) {
        file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("my-zip: cannot open file\n");
            return 1;
        }

        previous = fgetc(file);
        if (previous == EOF) {
            fclose(file);
            continue;
        }
        count = 1;
        // Read each character and count consecutive occurrences
        while ((current = fgetc(file)) != EOF) {
            if (current == previous) {
                count++;
            } else {
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&previous, sizeof(char), 1, stdout);
                previous = current;
                count = 1;
            }
        }
        // Write the last sequence
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&previous, sizeof(char), 1, stdout);
        fclose(file);
    }

    return 0;
}
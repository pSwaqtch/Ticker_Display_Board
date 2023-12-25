#include <stdio.h>
#include <string.h>

int main() {
    // Original 1D string
    char lines[] = "..........\n..........\n..........";

    // Variables for 2D conversion
    char char2D[10][15];

    // Initialize pointers to sentences
    char *token = strtok(lines, "\n");
    int i = 0;
    while (token != NULL && i <= 10) {
        strncpy(char2D[i], token, 15 - 1);
        char2D[i][15 - 1] = '\0';  // Ensure null-terminated
        token = strtok(NULL, "\n");
        i++;
    }

    // Print the 2D array
    for (int i = 0; i < 10; i++) {
        printf("Sentence %2d: %s\n", i + 1, char2D[i]);
    }

    return 0;
}

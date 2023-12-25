#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int height = 10;
const int asciiWidth = 15;
const int MAX_WIDTH = 15;

void appendChar(char finalSentence[][height][asciiWidth], char *characterAsciiLines, int charNum);
void searchAndAppendCharacter(int charNum, int widths[], char *characterAsciiLines, char inputString[], const char *filename);
void processUserInput(char inputString[], char finalSentence[][height][asciiWidth], int widths[]);
void printFinalSentence(int stringLength, int height, int widths[], char finalSentence[][height][asciiWidth]);
void convertTo2DArray(int stringLength, int height, int widths[], char finalSentence[][height][MAX_WIDTH], char newArray[][MAX_WIDTH * stringLength]);

int main() {

    char inputString[256];
    printf("Enter the string: ");
    fgets(inputString, sizeof(inputString), stdin);
    for (int i = 0; i < strlen(inputString); i++) {
        if (inputString[i] == ' ') {
            inputString[i] = '`';
        }
    }    inputString[strcspn(inputString, "\n")] = '\0';
    int stringLength = strlen(inputString);

    char newArray[height][MAX_WIDTH * stringLength];

    char finalSentence[stringLength][height][asciiWidth] = {};
    int widths[stringLength] = {};

    processUserInput(inputString, finalSentence, widths);

    // Print the 3D array
    //printFinalSentence(stringLength, height, widths, finalSentence);

    convertTo2DArray(stringLength, height, widths, finalSentence, newArray);

    int width=0;
    for (int i = 0; i < stringLength; ++i) {
        width+=widths[i];
    }
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%c",newArray[i][j]); 
        }
        printf("\n");
    }

    return 0;
}

void convertTo2DArray(int stringLength, int height, int widths[], char finalSentence[][height][MAX_WIDTH], char newArray[][MAX_WIDTH * stringLength]) {
    for (int j = 0; j < height; ++j) {
        int offset = 0;
        for (int i = 0; i < stringLength; ++i) {
            // Copy each string to the new array
            sprintf(newArray[j] + offset, "%s", finalSentence[i][j]);
            offset += widths[i];
        }
    }
}

void printFinalSentence(int stringLength, int height, int widths[], char finalSentence[][height][asciiWidth]){
    //for (int i = 0; i < stringLength; ++i)printf("%6d", widths[i]);printf("\n");
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < stringLength-1; ++i) {
            printf("%s", finalSentence[i][j]);
        }
        printf("%s\n", finalSentence[stringLength-1][j]);
    }
}

void processUserInput(char inputString[], char finalSentence[][height][asciiWidth], int widths[]) {
    char characterAsciiLines[256] = {};

    for (int charNum = 0; charNum < strlen(inputString); charNum++) {

        memset(characterAsciiLines, 0, sizeof(characterAsciiLines));
        searchAndAppendCharacter(charNum, widths, characterAsciiLines, inputString, "example_output.txt");

        appendChar(finalSentence, characterAsciiLines, charNum);
    }
}

void appendChar(char finalSentence[][height][asciiWidth], char *characterAsciiLines, int charNum) {
    // Initialize pointers to sentences
    char *token = strtok(characterAsciiLines, "\n");
    int i = 0;
    while (token != NULL && i < height) {
        strncpy(finalSentence[charNum][i], token, asciiWidth - 1);
        finalSentence[charNum][i][asciiWidth - 1] = '\0'; // Ensure null-terminated
        token = strtok(NULL, "\n");
        i++;
    }
}

void searchAndAppendCharacter(int charNum, int widths[], char *characterAsciiLines, char inputString[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    // Search for the specified character in the file
    char line[256] = {};
    while (fgets(line, sizeof(line), file)) {
        char *charPos = strchr(line, inputString[charNum]);

        // Check if the character is found within double quotes
        if (charPos != NULL && strchr(line, '~') < charPos && strchr(charPos, '~') > charPos) {
            // Character found, print the width
            int charWidth;
            if (sscanf(line, "%*[^0-9]%d", &charWidth) == 1) {
                //printf("Width: %d\n", charWidth);
                widths[charNum] = charWidth;
            }

            for (int i = 0; i < height && fgets(line, sizeof(line), file); ++i) {
                //printf("%s", line);
                strcat(characterAsciiLines, line);
            }
            break;
        }
        memset(line, 0, sizeof(line));
    }

    // Close the file
    fclose(file);
}

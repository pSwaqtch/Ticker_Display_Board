#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DELAY 500000
const int printWidth=90;
const int height = 10;
const int asciiWidth = 15;
const int MAX_WIDTH = 15;


void printBoard(int printWidth, int width, int l,int speed,char newArray[height][width],char inputString[]);
void arrayRev(char *str);
void appendChar(char finalSentence[][height][asciiWidth], char *characterAsciiLines, int charNum);
void searchAndAppendCharacter(int charNum, int widths[], char *characterAsciiLines, char inputString[], const char *filename);
void processUserInput(char inputString[], char finalSentence[][height][asciiWidth], int widths[]);
void printFinalSentence(int stringLength, int height, int widths[], char finalSentence[][height][asciiWidth]);
void convertTo2DArray(int stringLength, int height, int widths[], char finalSentence[][height][MAX_WIDTH], char newArray[][MAX_WIDTH * stringLength]);

void clearScreen() { printf("\033[H\033[J"); }

int main(){
	
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



    for (int i = 0; i < 10; i++) {
        arrayRev(newArray[i]);
    }

    int length=strlen(newArray[0]), speed, itteration;
    
    do {
        printf("Enter the speed (1 -- 10): ");
        scanf("%d", &speed);
        if (speed < 1 || speed > 10) {
            printf("Invalid speed! Please enter a speed between 1 and 10.\n");
        }
    } while (speed < 1 || speed > 10);

    do {
        printf("Enter the itteration (1 -- 5): ");
        scanf("%d", &itteration);
        if (itteration < 1 || itteration > 5) {
            printf("Invalid itteration! Please enter a itteration between 1 and 5.\n");
        }
    } while (itteration < 1 || itteration > 5);


    char printArray[height][width];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%c",newArray[i][j]);
            printArray[i][j]=newArray[i][j]; 
            printf("%c",printArray[i][j]);
        }
        printf("\n");
    }



	for (int i = 0; i < itteration; ++i) {
	   printBoard(printWidth,width,length,speed,printArray,inputString);
    }



    return 0;
}

void printBoard(int printWidth,int width, int l, int speed, char newArray[height][width],char inputString[]){


	for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%c",newArray[i][j]); 
        }
        printf("\n");
    }

    int size=strlen(inputString);

	int y=(printWidth-size)/2; //((((w-l)/2))+((w-l)%2))

    char stringRev[height][width];
    for (int i = 0; i < 2; i++) {
        strcpy(stringRev[i], newArray[i]);
        arrayRev(stringRev[i]);
    }

	for (int a = 0; a < printWidth+l+1; ++a) {
        clearScreen();
        
        printf("++");for (int i = 0; i < printWidth; ++i)printf("=");printf("++\n");
        printf("||");for (int i = 0; i < y; ++i)printf(".");printf("%s", inputString);for (int i = 0; i < printWidth-size-y; ++i)printf(".");printf("||\n");
        printf("++");for (int i = 0; i < printWidth; ++i)printf("=");printf("++\n");
        printf("||");for (int i = 0; i < printWidth; ++i)printf(".");printf("||\n");
    
    
        for (int q = 0; q < 10; ++q) {
            printf("||");
        
                for (int i = 0; i < a && i > l; ++i) {
                    printf(" ");
                }
        
                for (int i = 0; i < a; ++i) {
                    if(i < printWidth && a - i -1 < l){
                        printf("%c",newArray[q][a-i-1]);
                    }
                    else if (i < printWidth){
                        printf(".");
                    }
                }
        
                for (int i = printWidth-a-1; i >= 0 && i < printWidth; i--) {
                    printf(".");
                }
        
            printf("||\n");
        }
    
    
        printf("||");for (int i = 0; i < printWidth; ++i)printf(".");printf("||\n");
        printf("++");for (int i = 0; i < printWidth; ++i)printf("=");printf("++\n");
    
        usleep(DELAY/speed);
    }
}

void processUserInput(char inputString[], char finalSentence[][height][asciiWidth], int widths[]) {
    char characterAsciiLines[256] = {};

    for (int charNum = 0; charNum < strlen(inputString); charNum++) {

        memset(characterAsciiLines, 0, sizeof(characterAsciiLines));
        searchAndAppendCharacter(charNum, widths, characterAsciiLines, inputString, "ascii_letters.txt");

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

void arrayRev(char *str) {
    int length = strlen(str);
    int start = 0;
    int end = length - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}
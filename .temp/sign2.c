#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <windows.h>

#define DELAY 1000000
const int printWidth=30;
const int height = 10;
const int asciiWidth = 15;
const int MAX_WIDTH = 15;

void printBoard(int w, int l,int speed,char inputString[10][printWidth]);
void clearScreen() { printf("\033[H\033[J"); }
void arrayRev(char *str);

int main(){
    char inputString[10][30] = {
        "This is the String 0",
        "This is the String 1",
        "This is the String 2",
        "This is the String 3",
        "This is the String 4",
        "This is the String 5",
        "This is the String 6",
        "This is the String 7",
        "This is the String 8",
        "This is the String 9",
    };

    for (int i = 0; i < 10; i++) {
        arrayRev(inputString[i]);
    }

#include <stdlib.h>

    int length=strlen(inputString[0]), width=printWidth, speed, itteration;
    
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

    for (int i = 0; i < itteration; ++i) {
       printBoard(width,length,speed,inputString);
    }
}

void printBoard(int w, int l, int speed, char inputString[10][printWidth]){

    int y=(w-l)/2; //((((w-l)/2))+((w-l)%2))

    char stringRev[10][printWidth];
    for (int i = 0; i < 2; i++) {
        strcpy(stringRev[i], inputString[i]);
        arrayRev(stringRev[i]);
    }

    for (int a = 0; a < printWidth+l+1; ++a) {
        clearScreen();
        
        printf("++");for (int i = 0; i < w; ++i)printf("=");printf("++\n");
        printf("||");for (int i = 0; i < y; ++i)printf(".");printf("%s", stringRev);for (int i = 0; i < w-l-y; ++i)printf(".");printf("||\n");
        printf("++");for (int i = 0; i < w; ++i)printf("=");printf("++\n");
        printf("||");for (int i = 0; i < w; ++i)printf(".");printf("||\n");
    
    
        for (int q = 0; q < 10; ++q) {
            printf("||");
        
                for (int i = 0; i < a && i > l; ++i) {
                    printf(" ");
                }
        
                for (int i = 0; i < a; ++i) {
                    if(i < w && a - i -1 < l){
                        printf("%c",inputString[q][a-i-1]);
                    }
                    else if (i < w){
                        printf(".");
                    }
                }
        
                for (int i = w-a-1; i >= 0 && i < w; i--) {
                    printf(".");
                }
        
            printf("||\n");
        }
    
    
        printf("||");for (int i = 0; i < w; ++i)printf(".");printf("||\n");
        printf("++");for (int i = 0; i < w; ++i)printf("=");printf("++\n");
    
        usleep(DELAY/speed);
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
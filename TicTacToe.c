/** 2023 Hosung.Kim <hyongak516@mail.hongik.ac.kr>
 * 
 * TIC-TAC-TOE
 * 
*/


#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>

// ASCII
const int X = 88;
const int O = 79;
const int SPACE = 32;


void drawMap(char* map) {
    for (int i=0; i<3; i++) {
        printf("  +---+---+---+\n");
        printf("%d | %c | %c | %c |\n", 3-i, *(map+3*i), *(map+3*i+1), *(map+3*i+2));
    }
    printf("  +---+---+---+\n");
    printf("    a   b   c  \n");
}

// The score consists of 8 digits and each digit is x3 o3 x2 o2 x1 o1 x0 o0.
int getEvaluation(char* map) {
    int score = 9090909;
    // width 012 345 678
    for (int i=0; i<3; i++) {
        int oNum = 0;
        int xNum = 0;
        for (int j=0; j<3; j++) {
            if (*(map+3*i+j) == X) {
                xNum += 1;
            }
            if (*(map+3*i+j) == O) {
                oNum += 1;
            }
        }
        if (oNum == 0) {
            score += pow(10.0, (double)xNum*2+1);
        }
        if (xNum == 0) {
            score -= pow(10.0, (double)oNum*2);
        }
    }
    // height 036 147 258
    for (int i=0; i<3; i++) {
        int oNum = 0;
        int xNum = 0;
        for (int j=0; j<3; j++) {
            if (*(map+i+3*j) == X) {
                xNum += 1;
            }
            if (*(map+i+3*j) == O) {
                oNum += 1;
            }
        }
        if (oNum == 0) {
            score += pow(10.0, (double)xNum*2+1);
        }
        if (xNum == 0) {
            score -= pow(10.0, (double)oNum*2);
        }
    }
    // diagonal 048 246
    for (int i=0; i<2; i++) {
        int oNum = 0;
        int xNum = 0;
        for (int j=0; j<3; j++) {
            if (*(map+2*i+2*(2-i)*j) == X) {
                xNum += 1;
            }
            if (*(map+2*i+2*(2-i)*j) == O) {
                oNum += 1;
            }
        }
        if (oNum == 0) {
            score += pow(10.0, (double)xNum*2+1);
        }
        if (xNum == 0) {
            score -= pow(10.0, (double)oNum*2);
        }
    }
    return score;
}

int main() {
    system("CLS");
    char map[9] = "         ";
    /**
     *     +---+---+---+
     *  3  |   |   |   |
     *     +---+---+---+
     *  2  |   |   |   |
     *     +---+---+---+
     *  1  |   |   |   |
     *     +---+---+---+ 
     *       a   b   c
    */

    for (int i=0; i<3; i++) {
        printf("  +---+---+---+\n");
        printf("%d | a%d| b%d| c%d|\n", 3-i, 3-i, 3-i, 3-i);
    }
    printf("  +---+---+---+\n");
    printf("    a   b   c  \n");

    char x;
    char y;
    int tempCoordinate;
    
    while (1) {
        // player's turn
        printf("Please enter coordinate : ");
        x = getchar();
        y = getchar();
        while (getchar() != '\n') {
        }
        
        if (x == 97 || x == 98 || x == 99) {
            tempCoordinate = x-97;
        } else {
            printf("Please enter the correct coordinate.\n");
            continue;
        }
        if (y == 49 || y == 50 || y == 51) {
            tempCoordinate += (51-y)*3;
        } else {
            printf("Please enter the correct coordinate.\n");
            continue;
        }
        if (map[tempCoordinate] != SPACE) {
            printf("Please enter a valid coordinate.\n");
            continue;
        }
        map[tempCoordinate] = 'X';
        system("CLS");
        drawMap(map);

        // check if player won
        if (getEvaluation(map) >= 10000000) {
            printf(" _    ______________________  ______  __\n| |  / /  _/ ____/_  __/ __ \\/ __ \\ \\/ /\n| | / // // /     / / / / / / /_/ /\\  / \n| |/ // // /___  / / / /_/ / _, _/ / /  \n|___/___/\\____/ /_/  \\____/_/ |_| /_/   \n");

            for (int i=0; i<10; i++) {
                printf("\n\rTIC-TAC-TOE will be terminated in %d seconds.", 10-i);
                Sleep(1000);
            }
            return 0;
        }

        // check if player drawed
        int flag = 0;
        for (int i=0; i<9; i++) {
            if (map[i] == SPACE) {
                flag = 1;
            }
        }
        if (flag == 0) {
            printf("    ____  ____  ___ _       __\n   / __ \\/ __ \\/   | |     / /\n  / / / / /_/ / /| | | /| / / \n / /_/ / _, _/ ___ | |/ |/ /  \n/_____/_/ |_/_/  |_|__/|__/   \n");
            for (int i=0; i<10; i++) {
                printf("\n\rTIC-TAC-TOE will be terminated in %d seconds.", 10-i);
                Sleep(1000);
            }
            return 0;
        }

        // ai's turn
        int score[9];
        for (int i=0; i<9; i++) {
            if (map[i] == SPACE) {
                char tempMap[9];
                for (int j=0; j<9; j++) {
                    tempMap[j] = map[j];
                }
                tempMap[i] = 'O';
                score[i] = getEvaluation(tempMap);
            } else {
                score[i] = 100000000;
            }
        }
        int minScore = 100000000;
        int minIndex;
        for (int i=0; i<9; i++) {
            if (score[i] <= minScore) {
                minScore = score[i];
                minIndex = i;
            }
        }
        map[minIndex] = 'O';
        system("CLS");
        drawMap(map);
        // check if player lose
        if (getEvaluation(map) < 9000000) {
            printf("    ____  _____________________  ______\n   / __ \\/ ____/ ____/ ____/   |/_  __/\n  / / / / __/ / /_  / __/ / /| | / /   \n / /_/ / /___/ __/ / /___/ ___ |/ /    \n/_____/_____/_/   /_____/_/  |_/_/     \n");
            for (int i=0; i<10; i++) {
                printf("\n\rTIC-TAC-TOE will be terminated in %d seconds.", 10-i);
                Sleep(1000);
            }
            return 0;
        }
        
    }
    return 0;
}
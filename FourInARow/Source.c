#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)
int board[6][7], row[6];

bool checkName(char* name) { // SARA'S METHOD
    // ADD REMOVE THE SPACES AND REMOVE THE NEXT LINE
    for (int i = 0; i < 40; i++)
        if (name[i] == '\n') {
            name[i] = '\0';
            break;
        }
    return true;
}

bool checkMove(int tempCol, int* row) { // board is NxN, row is N

    if (tempCol < 0 || tempCol > 6) {
        printf("ERROR: INVALID COLUMN CHOICE \n CHOOSE AGAIN:");
        return false;
    }

    if (row[tempCol] > 5) {
        printf("ERROR: COLUMN IS FULL \n CHOOSE AGAIN:");
        return false;
    }

    return true;

}

void printBoard() { printf("PRINTING BOARD HERE\n");} // AHMAD'S METHOD

bool checkWin() { return false; } // KARIM'S METHOD

int main() {

    /*Initliaze BOARD and ROW*/

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            board[i][j] = 0;

    for (int i = 0; i < 6; i++)
        row[i] = 0;

	/** ASSIGN NAMES AND PLAYERS**/
    char name1[40];
    char name2[40];
    printf("Enter the first name:");
    fgets(name1, 20, stdin);
    while (!checkName(name1)) {
        printf("ERROR: NAME CONTAINS SPACE\nTRY AGAIN: ");
        scanf("%[^\n]%c",name1);
    }
    printf("Enter the second name:"); // WHAT IF SAME NAME
    fgets(name2, 20, stdin);
    while (!checkName(name2)) {
        printf("ERROR: NAME CONTAINS SPACE\nTRY AGAIN: ");
        scanf("%[^\n]%c", name2);
    }

    printf("Current Board: \n");
    printBoard();
    printf("\n");

    int coin = rand() % 2;
    char* player1 = (coin == 0) ? name1 : name2;
    char* player2 = (coin == 0) ? name2 : name1;

    printf("\nAfter flipping a coin, we have the following:\nPlayer1: %s\nPlayer2: %s\n\n", player1, player2);
    
    int currentToken, tempCol, winner = 0;
    char* currentPlayer;

    /* START GAME (42 TURNS)*/
    for (int i = 1; i <= 42; i++) {
        currentToken = (i % 2 == 1) ? 1 : 2; // if odd then player 1
        currentPlayer = (i % 2 == 1) ? player1 : player2;
        printf("%s's turn \n", currentPlayer);
        printf("Input a column : ");
        // HERE START THE TIMER
        do {
            // scanf("%[^\n]%c", currentCol); // ASK DR
            scanf("%d", &tempCol);
            tempCol--;
        } while (!checkMove(tempCol, row));
        // HERE END THE TIMER AND ADD ACCORDINGLY

        // update board
        board[row[tempCol]][tempCol] = currentToken;
        printf("%d ", board[row[tempCol]][tempCol]);
        row[tempCol]++;

        if (checkWin()) {
            winner = currentToken;
            break;
        }

        printBoard();

    }


    /*END GAME : CHOOSE WINNER ACCORDINGLY*/
    if (winner != 0) {
        printBoard();
        printf("Winner is %s!\n", winner == 1 ? player1 : player2);
    }

    else {
        printf("It's a tie!\n"); // HERE CHECK WHICH TIMER IS FASTER AND CHOOSE ACCORDINGLY
        printf("%s wins because of faster gameplay.", player1);
    }


	return 0;

}
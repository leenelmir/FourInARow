#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)
int board[6][7], row[6];

void resetName(char* name){
for (int i = 0; i < 21; i++)
    name[i] = '-';
}
bool checkEmptyScanner(char* name) { // CHECK WHETHER SCANNER IS EMPTY, IF EMPTY, REMOVE \n

for (int i = 0; i<21; i++){
    if (name[i] == '\n'){
    name[i] = '\0';
    return true;
    }
}
return false;

}

bool checkSpace(char* name){

for (int i = 0; i<21; i++)
if (name[i] == ' ')
 return false;

 return true;


}

bool checkValidMove(int tempCol, int* row){
     if (tempCol < 0 || tempCol > 6) {
            printf("ERROR: INVALID COLUMN CHOICE");
            return false;
        }

        if (row[tempCol] > 5) {
            printf("ERROR: COLUMN IS FULL");
            return false;
        }

        return true;
}

void printBoard() {

    printf("---------------\n");
        
        for (int i = 0; i < 6; i++)
        {
           printf("|");
            for (int j = 0; j < 7; j++)
            {
                printf("%d" ,board[i][j]);
                printf("|");
            }
            printf("\n");
            
        }

    printf("---------------\n");

}

bool checkWin(int player, int board[6][7]) {
	//check for 4 horizontal
	int i, j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 7-3; j++) {
			if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player) {
				return true;
			}
		}
	}
	//check for 4 vertical
	for (i = 0; i < 6 - 3; i++) {
		for (j = 0; j < 7; j++) {
			if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player) {
				return true;
			}
		}
	}
    //check up diagonal
		for(i = 3; i < 6; i++){
			for(j = 0; j < 7 - 3; j++){
				if (board[i][j] == player   && board[i-1][j+1] == player && board[i-2][j+2] == player && board[i-3][j+3] == player)
                {
					return true;
				}
			}
		}
		//check down diagonal
		for(i = 0; i < sizeof(board)/sizeof(board[0]) - 3; i++){
			for(j = 0; j < sizeof(board[0]) - 3; j++){
				if (board[i][j] == player   && board[i+1][j+1] == player && board[i+2][j+2] == player && board[i+3][j+3] == player)
                {
                    return true;
                }
				}
			}
		return false;
	}

int main() {

    /*Initliaze BOARD and ROW*/

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            board[i][j] = 0;

    for (int i = 0; i < 6; i++)
        row[i] = 0;

	/** ASSIGN NAMES AND PLAYERS**/
    char name1[21];
    char name2[21];
    char c;
    printf("ENTER PLAYER NAMES (ONLY FIRST 20 CHARACTERS WILL BE READ): \n");
    printf("Enter the first name:");
    fgets(name1, 21, stdin);
    if (!checkEmptyScanner(name1))
        while ((c = getchar())!= '\n') {}

    while (!checkSpace(name1)) {
        printf("ERROR: NAME CONTAINS SPACE\nTRY AGAIN: ");
        resetName(name1); // RESETS THE STRING TO EMPTY
        fgets(name1, 21, stdin);
        if (!checkEmptyScanner(name1))
            while ((c = getchar()) != '\n') {}

    }
    printf("Enter the second name:"); // WHAT IF SAME NAME
    fgets(name2, 21, stdin);
    if (!checkEmptyScanner(name2))
        while ((c = getchar())!= '\n') {}
    while (!checkSpace(name2)) {
        printf("ERROR: NAME CONTAINS SPACE\nTRY AGAIN: ");
        resetName(name2);
        fgets(name2, 21, stdin);
        if (!checkEmptyScanner(name2))
            while ((c = getchar()) != '\n') {}
    }

     
        
    for (int i = 0; i < 6; i++)           // Initially fills the board with 0s
        {
            for (int j = 0; j < 7; j++)
            {
                board[i][j] = 0;
            }
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
        printf("Input a column (ONLY FIRST CHARACTER WILL BE READ): ");
        // HERE START THE TIMER

        int tempCol;
        char c;
        tempCol = getchar() - 48 - 1; // casts ASCII value to (-48) then converts to zero-index (-1)

        while (tempCol != -39 && (c=getchar()) != '\n') {}
        while (!checkValidMove(tempCol, row)){ // checks that column is within range and available
             printf("TRY AGAIN: ");
             tempCol = getchar() - 48 - 1;
             while (tempCol != -39 && (c=getchar()) != '\n') {}
            }
        // HERE END THE TIMER AND ADD ACCORDINGLY

        // update board
        board[6-row[tempCol]-1][tempCol] = currentToken;
        row[tempCol]++;

        //if (checkWin(currentToken,board)) {
          //  winner = currentToken;
            //break;
        //}

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
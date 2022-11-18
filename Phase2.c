
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>

int* board[6], row[6];
int difficulty = 0; // 0 easy : 2 steps ahead, 1 medium: 3 steps ahead, 2 hard: 4 steps ahead

void resetName(char* name) { //to avoid overwriting previous input when invalid input is inserted
    for (int i = 0; i < 21; i++)
        name[i] = '-';
}
bool checkEmptyScanner(char* name) { // CHECK WHETHER SCANNER IS EMPTY, IF EMPTY, REMOVE \n

    for (int i = 0; i < 21; i++) {
        if (name[i] == '\n') {
            name[i] = '\0';
            return true;
        }
    }
    return false;

}

bool checkSpace(char* name) {

    for (int i = 0; i < 21; i++)
        if (name[i] == ' ')
            return false;

    return true;
}

bool checkValidMove(int tempCol, int* row) {
    if (tempCol < 0 || tempCol > 6) {
        printf("ERROR: INVALID COLUMN CHOICE\n");
        return false;
    }

    if (row[tempCol] > 5) {
        printf("ERROR: COLUMN IS FULL\n");
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
            printf("%d", board[i][j]);
            printf("|");
        }
        printf("\n");

    }

    printf("---------------\n");

}


bool checkWin(int** board, int player) {

     //check for 4 horizontal
    int i, j;
    for (i = 0; i < 6; i++)
        for (j = 0; j < 7 - 3; j++)
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player)
                return true;

    //check for 4 vertical
    for (i = 0; i < 6 - 3; i++)
        for (j = 0; j < 7; j++)
            if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player)
                return true;

    //check up diagonal
    for (i = 3; i < 6; i++)
        for (j = 0; j < 7 - 3; j++)
            if (board[i][j] == player && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player && board[i - 3][j + 3] == player)
                return true;

    //check down diagonal
    for (i = 0; i < 6 - 3; i++)
        for (j = 0; j < 7 - 3; j++)
            if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[i + 3][j + 3] == player)
                return true;

    return false;
}

int findClosestWin(int** board, int steps, int player) { // find closest win/farthest loss for the PLAYER

    int count = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            count = count + ((board[i][j] == 1 || board[i][j] == 2) ? 1 : 0);

    int minSteps = 100;
    int*** queue = (int***)(malloc(5000 * sizeof(int**))); // no more than 7^4 scenarios // steps cannot exceed 4
    if (queue != NULL)
        for (int i = 0; i < 5000; i++) {
            queue[i] = (int**)malloc(6 * sizeof(int*));
            if (queue[i] != NULL)
                for (int j = 0; j < 6; j++)
                    queue[i][j] = (int*)malloc(7 * sizeof(int));
        }

    int head = 0, tail = 0, size = 0;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            if (queue != NULL && queue[tail] != NULL && queue[tail][i] != NULL) // make sure all space was allocated
                queue[tail][i][j] = board[i][j];
    tail++;
    size++;

    // intialize current and temp
    int* current[6];
    int n0[7] = { 0,0,0,0,0,0,0 };
    current[0] = n0;
    int n1[7] = { 0,0,0,0,0,0,0 };
    current[1] = n1;
    int n2[7] = { 0,0,0,0,0,0,0 };
    current[2] = n2;
    int n3[7] = { 0,0,0,0,0,0,0 };
    current[3] = n3;
    int n4[7] = { 0,0,0,0,0,0,0 };
    current[4] = n4;
    int n5[7] = { 0,0,0,0,0,0,0 };
    current[5] = n5;

    int temp[6][7] = { {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0} };

    while (head < size) {

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 7; j++)
                current[i][j] = queue[head][i][j];

        head++; // dequeue prev head
        size--;

        int indices[7] = { 6,6,6,6,6,6,6 }; // initialize all column indices to full

        int count1s = 0, count2s = 0;
        for (int i = 0; i < 7; i++)	// for each column        
            for (int j = 0; j < 6; j++)	// record what row index we can insert at now      
                if (current[j][i] == 0)
                    indices[i] = j;

                else if (current[j][i] == 1)
                    count1s++;
                else
                    count2s++;

        int numOfMoves = count2s + count1s - count;

        if (numOfMoves > steps)
            break;

        if (checkWin(current, 1)) {
            if (abs(minSteps) > numOfMoves)
                minSteps = (player == 1 ? 1 : -1) * numOfMoves;

            continue;
        }

        if (checkWin(current, 2))
        {
            if (abs(minSteps) > numOfMoves)
                minSteps = (player == 1 ? -1 : 1) * numOfMoves;

            continue;
        }


        for (int j = 0; j < 7; j++)	// add every possible neighbor (adding the number at each column)    
        {

            if (indices[j] == 6) // cannot insert at this column
                continue;

            for (int k = 0; k < 6; k++)
                for (int l = 0; l < 7; l++)
                    temp[k][l] = current[k][l];

            temp[indices[j]][j] = count1s > count2s ? 2 : 1;	// choose player for this height               
            for (int k = 0; k < 6; k++)
                for (int l = 0; l < 7; l++)
                    queue[tail][k][l] = temp[k][l];

            tail++; // enqueue neighbors
            size++;
        }

    }

    // deallocate space for queue
    for (int i = 0; i < 5000; i++) {
        if (queue[i] != NULL) {
            for (int j = 0; j < 6; j++) {
                free(queue[i][j]);
            }
            free(queue[i]);
        }
    }
    free(queue);

    return minSteps;
}


int findBotRank(int** board) { // how to know if player 1 or player 2? 


    int c1 = 0, c2 = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 1) c1++;
            if (board[i][j] == 2) c2++;
        }

    return c1 <= c2 ? 1 : 2;
}

int* tryNextMove(int** board, int player) {
   
    int* nextMoves = (int*)malloc(7 * sizeof(int));
    for (int i = 0; i < 7; i++)
        if (nextMoves != NULL)
            nextMoves[i] = 101;

    int indices[7] = { 6,6,6,6,6,6,6 };
    int* tempBoard[6];
    int n0[7] = { 0,0,0,0,0,0,0 };
    tempBoard[0] = n0;
    int n1[7] = { 0,0,0,0,0,0,0 };
    tempBoard[1] = n1;
    int n2[7] = { 0,0,0,0,0,0,0 };
    tempBoard[2] = n2;
    int n3[7] = { 0,0,0,0,0,0,0 };
    tempBoard[3] = n3;
    int n4[7] = { 0,0,0,0,0,0,0 };
    tempBoard[4] = n4;
    int n5[7] = { 0,0,0,0,0,0,0 };
    tempBoard[5] = n5;

    for (int i = 0; i < 7; i++)	// for each column        
        for (int j = 0; j < 6; j++)	// record what row index we can insert at now      
            if (board[j][i] == 0)
                indices[i] = j;

    for (int k = 0; k < 7; k++) {

        if (indices[k] == 6)
            continue;

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 7; j++)
                tempBoard[i][j] = board[i][j];

        tempBoard[indices[k]][k] = player;

        if (nextMoves != NULL)
            nextMoves[k] = findClosestWin(tempBoard, difficulty + 1, player); // store its closest move if starting at column k
        // difficulty + 1 = number of steps to make AFTER MAKING FIRST STEP

    }

    return nextMoves;
}


int columnPicker(int arr[])
{
    int lowest = arr[0];
    int numberOfUpdates = 0;

    if (lowest == 0)
        return 0;

    int currentLowestIndex = 0;
    for (int i = 1; i < 7; i++)
    {
        if(arr[i] != 101)
        {
            if (arr[i] >= 0 && lowest < 0)
            {
                lowest = arr[i];
                currentLowestIndex = i;
                numberOfUpdates++;
            }

            else if (arr[i] >= 0 && arr[i] < lowest)
            {
                lowest = arr[i];
                currentLowestIndex = i;
                numberOfUpdates++;
            }

            else if (arr[i] < 0 && lowest < 0 && arr[i] < lowest)
            {
                if (arr[i] < lowest)
                {
                    lowest = arr[i];
                    currentLowestIndex = i;
                    numberOfUpdates++;
                }
            }
            else if (arr[i] < 0 && lowest > 100)
            {
                lowest = arr[i];
                currentLowestIndex = i;
                numberOfUpdates++;
            }
        }
    }
    if (numberOfUpdates != 0)
        return currentLowestIndex;

    int randomIndex = rand() % 7;
    return randomIndex;

}

int makeMove(int** board) {
 
    int player = findBotRank(board);
    int steps = difficulty + 2; // difficulty 2 : hard : 4 steps ahead
    
    //printf("bot is player: %d\n", player); 
    
    int* nextMoves = tryNextMove(board, player); // try making FIRST MOVE at each column
   
    // for (int i = 0; i < 7; i++)
      //  printf("%d ", nextMoves[i]);
    
    int nextMove = columnPicker(nextMoves); // pick the best option from all of them 
    free(nextMoves);
    
   // printf("insert %d at column %d\n", player, nextMove); 
    
    return nextMove; // return the optimal choice of column
}


int main() {

    /*Initialize BOARD and ROW*/

    int n0[7] = { 0,0,0,0,0,0,0 };
    board[0] = n0;
    int n1[7] = { 0,0,0,0,0,0,0 };
    board[1] = n1;
    int n2[7] = { 0,0,0,0,0,0,0 };
    board[2] = n2;
    int n3[7] = { 0,0,0,0,0,0,0 };
    board[3] = n3;
    int n4[7] = { 0,0,0,0,0,0,0 };
    board[4] = n4;
    int n5[7] = { 0,0,0,0,0,0,0 };
    board[5] = n5;

    for (int i = 0; i < 6; i++)
        row[i] = 0;

    /* ASSIGN NAMES AND PLAYERS*/
    char name1[21];
    char c;
    printf("ENTER PLAYER NAME (ONLY FIRST 20 CHARACTERS WILL BE READ): \n");
    printf("Enter the first name:");
    fgets(name1, 21, stdin);
    if (!checkEmptyScanner(name1))
        while ((c = getchar()) != '\n') {}

    while (!checkSpace(name1)) {
        printf("ERROR: NAME CONTAINS SPACE\nTRY AGAIN: ");
        resetName(name1); // RESETS THE STRING TO EMPTY
        fgets(name1, 21, stdin);
        if (!checkEmptyScanner(name1))
            while ((c = getchar()) != '\n') {}

    }

    printf("CHOOSE DIFFICULTY (0,1,2):  ");
    difficulty = getchar() - 48; // casts ASCII value to int (-48) then converts to zero-index (-1)
  
    while (difficulty != -38 && (c = getchar()) != '\n') {}
    while ((difficulty < 0 || difficulty > 2)) { // checks that column is within range and available
        printf("\nTRY AGAIN: ");
        difficulty = getchar() - 48;
        while (difficulty != -38 && (c = getchar()) != '\n') {}
    }

    printf("difficulty selected: %d\n", difficulty);
    printf("Current Board: \n");
    printBoard();
    printf("\n");

    int coin = rand() % 2;
    char* name2 = "bot";
    char* player1 = (coin == 0) ? name1 : name2;
    char* player2 = (coin == 0) ? name2 : name1;

    long total = 0;
    long total_t_1 = 0;                 //time for both players intially set to zero
    long total_t_2 = 0;

    printf("\nAfter flipping a coin, we have the following:\nPlayer1: %s\nPlayer2: %s\n\n", player1, player2);

    int currentToken, tempCol, winner = 0;
    char* currentPlayer;

    /* START GAME (42 TURNS)*/

    for (int i = 1; i <= 42; i++) {
        time_t start, end;
        total = 0;
        currentToken = (i % 2 == 1) ? 1 : 2; // if odd then player 1
        currentPlayer = (i % 2 == 1) ? player1 : player2;

        printf("%s's turn \n", currentPlayer);
        if ((i%2 ==1 && coin == 1) || (i%2 == 0 && coin == 0)){ // if current player is the bot 
            time(&start);
            tempCol = makeMove(board);
            time(&end);
        }
        
        else {
        printf("Input a column from 0 to 6 (ONLY FIRST CHARACTER WILL BE READ): ");
        // HERE START THE TIMER
        time(&start);
        char c;
        tempCol = getchar() - 48; // casts ASCII value to (-48) then converts to zero-index (-1)

        while (tempCol != -38 && (c = getchar()) != '\n') {}
        while (!checkValidMove(tempCol, row)) { // checks that column is within range and available
            printf("\nTRY AGAIN: ");
            tempCol = getchar() - 48;
            while (tempCol != -38 && (c = getchar()) != '\n') {}
        }
        // HERE END THE TIMER AND ADD ACCORDINGLY
        time(&end);
        }
        total = (long)difftime(end, start);

        if (currentToken == 1)       //then it is currently player1
            total_t_1 += total;

        else
            total_t_2 += total;
        

        // update board
        board[6 - row[tempCol] - 1][tempCol] = currentToken;
        row[tempCol]++;

        if (checkWin(board,currentToken)) {

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

        if (total_t_1 > total_t_2)
            printf("Player 1 took %lu seconds.\nPlayer 2 took %lu seconds.\n%s wins because of faster gameplay.", total_t_1, total_t_2, player2);
        else if (total_t_2 > total_t_1)
            printf("Player 1 took %lu seconds.\nPlayer 2 took %lu seconds.\n%s wins because of faster gameplay.", total_t_1, total_t_2, player1);
        else
            printf("Both players tied again in time (which is impressive). Total time taken by both players: %lu", total_t_1);
    }


    return 0;

}
